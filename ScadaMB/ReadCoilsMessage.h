#pragma once

#include "ModbusMessageTCP.h"

class ReadCoilsMessage : ModbusMessageTCP
{
private:
	unsigned short startingAddress;
	unsigned short quantityOfCoils;

	unsigned short byteCount;
	char* coilStatus;
public:
	ReadCoilsMessage();
	ReadCoilsMessage(char* bytes);
	virtual char* Serialize();
	virtual void Deserialize(char* msg);
};
