#include "ModbusDriverTCP.h"
#include "ReadCoilsMessage.h"
#include "ReadDescreteInputsMessage.h"
#include "ReadHoldingRegistersMessage.h"
#include "ReadInputRegistersMessage.h"
#include "WriteSingleCoilMessage.h"
#include "WriteSingleRegisterMessage.h"
#include "ErrorMessage.h"

ModbusDriverTCP * ModbusDriverTCP::instance = NULL;

ModbusMessageTCP* ModbusDriverTCP::ProcessAccessBuffer(char* buffer)
{
	switch (buffer[7])
	{
		case ModbusMessageTypes::READ_COILS:
			return new ReadCoilsMessage(buffer);
		case ModbusMessageTypes::READ_DESCRETE_INPUTS:
			return new ReadDescreteInputsMessage(buffer);
		case ModbusMessageTypes::READ_HOLDING_REGISTERS:
			return new ReadHoldingRegistersMessage(buffer);
		case ModbusMessageTypes::READ_INPUT_REGISTERS:
			return new ReadInputRegistersMessage(buffer);
		case ModbusMessageTypes::WRITE_SINGLE_COIL:
			return new WriteSingleCoilMessage(buffer);
		case ModbusMessageTypes::WRITE_SINGLE_REGISTER:
			return new WriteSingleRegisterMessage(buffer);
		default:
			return new ErrorMessage(buffer);
	}
}

ModbusDriverTCP * ModbusDriverTCP::Instance()
{
	if (instance == NULL) {
		instance = new ModbusDriverTCP();
	}
	return instance;
}

ModbusMessageTCP* ModbusDriverTCP::SendModbusMessage(SocketStruct* soc, ModbusMessageTCP* modbusMessage)
{
	this->sendMutex.lock();
	char* msg = modbusMessage->Serialize();
	bool success = SocketWrapper::Instance()->Send(soc, msg, modbusMessage->GetMessageLength());
	delete[] msg;
	ModbusMessageTCP* ret = NULL;

	if (success)
	{
		ret = this->Receive(soc);
	}
	this->sendMutex.unlock();
	return ret;
}

ModbusMessageTCP* ModbusDriverTCP::Receive(SocketStruct* socket)
{
	int index = 0;
	int messageLength = 0;
	int dataLengthCount = -1;

	socket->lock.lock();
	while (true) {

		int iResultSelect = SocketWrapper::Instance()->Select(socket->socket, 0);
		if (iResultSelect == SOCKET_ERROR)
		{
			continue;
		}

		if (iResultSelect == 0)
		{
			this_thread::sleep_for(chrono::milliseconds(20));
			continue;
		}

		int iResult = recv(socket->socket, &accessBuffer[index], accessBufferLength - index, 0);
		
		if (iResult == SOCKET_ERROR) break;
		if (iResult == 0) break;

		index += iResult;
		if (index >= 6 && messageLength == 0)
		{
			messageLength = ntohs(*(unsigned short*)&accessBuffer[4]) + 6;
			dataLengthCount = messageLength - index;
		}
		else if(messageLength != 0)
		{
			dataLengthCount -= iResult;
		}
		if (dataLengthCount == 0) break;

	}
	socket->lock.unlock();
	return this->ProcessAccessBuffer(accessBuffer);
}
