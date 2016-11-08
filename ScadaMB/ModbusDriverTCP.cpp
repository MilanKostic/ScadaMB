#include "ModbusDriverTCP.h"

ModbusMessageTCP ModbusDriverTCP::SendModbusMessage(SOCKET socket, ModbusMessageTCP modbusMessage)
{
	Socket::Instance()->Send(socket, modbusMessage.Serialize(), modbusMessage.GetMessageLength());
	
	return ModbusMessageTCP();
}

ModbusMessageTCP ModbusDriverTCP::Receive(SOCKET socket)
{
	char accessBuffer[1024];
	while (1) {

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

		int iResult = recv(socket, accessBuffer, 1024, 0);

		if (iResult == SOCKET_ERROR)
		{
			break;
		}

		if (iResult == 0)
		{
			break;
		}
	}
	//ProcessAccessBuffer(accessBuffer, iResult, bufferInfo, buffers);
	closesocket(socket);
	return ModbusMessageTCP();
}
