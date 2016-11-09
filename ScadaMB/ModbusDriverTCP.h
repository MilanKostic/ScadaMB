#pragma once
#include "ModbusMessageTCP.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Socket.h"

class ModbusDriverTCP
{
private:
	static ModbusDriverTCP *instance;
	static const unsigned short accessBufferLength = 1024;
	char accessBuffer[accessBufferLength];
	
public:
	ModbusMessageTCP* ProcessAccessBuffer(char* buffer);
	static ModbusDriverTCP *Instance();
	ModbusMessageTCP* SendModbusMessage(SOCKET socket, ModbusMessageTCP modbusMessage);
	ModbusMessageTCP* Receive(SOCKET socket);
};