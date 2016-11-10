#include "ModbusDriverTCP.h"
#include "ReadCoilsMessage.h"
#include "ReadDescreteInputsMessage.h"
#include "ReadHoldingRegistersMessage.h"
#include "ReadInputRegistersMessage.h"
#include "WriteSingleCoilMessage.h"
#include "WriteSingleRegisterMessage.h"

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
	}

	return new ModbusMessageTCP();
}

ModbusMessageTCP* ModbusDriverTCP::SendModbusMessage(SOCKET socket, ModbusMessageTCP* modbusMessage)
{
	bool success = Socket::Instance()->Send(socket, modbusMessage->Serialize(), modbusMessage->GetMessageLength());
	
	return this->Receive(socket);
}

ModbusMessageTCP* ModbusDriverTCP::Receive(SOCKET socket)
{
	int index = 0;
	int messageLength = 0;
	int dataLengthCount = -1;

	while (true) {

		int iResultSelect = Socket::Instance()->Select(socket, 0);
		if (iResultSelect == SOCKET_ERROR)
		{
			continue;
		}

		if (iResultSelect == 0)
		{
			Sleep(20);
			continue;
		}

		int iResult = recv(socket, &accessBuffer[index], accessBufferLength - index, 0);
		
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
	return this->ProcessAccessBuffer(accessBuffer);
}
