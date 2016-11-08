#pragma once
#include "ModbusMessageTCP.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Socket.h"

class ModbusDriverTCP
{
private:
	static const unsigned short accessBufferLength = 1024;
	char accessBuffer[accessBufferLength];
	ModbusMessageTCP ProcessAccessBuffer(char* buffer, int length);
public:
	ModbusMessageTCP SendModbusMessage(SOCKET socket, ModbusMessageTCP modbusMessage);
	ModbusMessageTCP Receive(SOCKET socket);
};