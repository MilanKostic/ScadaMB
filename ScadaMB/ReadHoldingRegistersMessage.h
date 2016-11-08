#pragma once

#include "ModbusMessageTCP.h"

class ReadHoldingRegistersMessage : ModbusMessageTCP
{
private:
	unsigned short startingAddress;
	unsigned short quantityOfRegisters;

	unsigned short byteCount;
	unsigned short* registerValue;
public:
	ReadHoldingRegistersMessage();
	ReadHoldingRegistersMessage(char* bytes);
	virtual char* Serialize();
	virtual void Deserialize(char* buffer);
};