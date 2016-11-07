#pragma once
#include "ModbusMessageTCP.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Socket.h"

class ModbusDriverTCP
{
private:
	
public:
	ModbusMessageTCP SendModbusMessage(SOCKET socket, ModbusMessageTCP modbusMessage);
	ModbusMessageTCP Receive(SOCKET socket);
};