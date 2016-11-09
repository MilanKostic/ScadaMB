#include "ModbusDriverTCP.h"
#include "ReadCoilsMessage.h"
#include "ReadDescreteInputsMessage.h"

ModbusDriverTCP* ModbusDriverTCP::instance = NULL;

ModbusMessageTCP* ModbusDriverTCP::ProcessAccessBuffer(char* buffer)
{
	switch (buffer[7])
	{
		case ModbusMessageTypes::READ_COILS:
			return (ModbusMessageTCP*)new ReadCoilsMessage(buffer);
		case ModbusMessageTypes::READ_DESCRETE_INPUTS:
			return (ModbusMessageTCP*)new ReadDescreteInputsMessage(buffer);
	}

	return new ModbusMessageTCP();
}

ModbusDriverTCP * ModbusDriverTCP::Instance()
{
	if (instance == NULL) {
		instance = new ModbusDriverTCP();
	}
	return instance;
}

ModbusMessageTCP* ModbusDriverTCP::SendModbusMessage(SOCKET socket, ModbusMessageTCP modbusMessage)
{
	Socket::Instance()->Send(socket, modbusMessage.Serialize(), modbusMessage.GetMessageLength());
	
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
			messageLength = *(unsigned short*)&accessBuffer[4] + 6;
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
