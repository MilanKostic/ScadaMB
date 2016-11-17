#pragma once
#include "ModbusMessageTCP.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "SocketWrapper.h"

class ModbusDriverTCP
{
private:
	static ModbusDriverTCP *instance;
	mutex mLocl;
	static const unsigned short accessBufferLength = 1024;
	char accessBuffer[accessBufferLength];
	ModbusMessageTCP* ProcessAccessBuffer(char* buffer);
	mutex sendMutex;
public:
	static ModbusDriverTCP *Instance();
	//mutex* GetMutex();
	ModbusMessageTCP* SendModbusMessage(SocketStruct* socket, ModbusMessageTCP* modbusMessage);
	ModbusMessageTCP* Receive(SocketStruct* socket);
};