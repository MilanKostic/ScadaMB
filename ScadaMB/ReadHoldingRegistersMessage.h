#pragma once

#include "ModbusMessageTCP.h"

class ReadHoldingRegistersMessage : public ModbusMessageTCP
{
private:
	unsigned short startingAddress;
	unsigned short quantityOfRegisters;

	unsigned short byteCount;
	unsigned short* registerValue;
public:
	ReadHoldingRegistersMessage(unsigned short length, unsigned short startingAddress, unsigned short quantityOfRegisters);
	ReadHoldingRegistersMessage();
	ReadHoldingRegistersMessage(char* bytes);
	virtual char* Serialize();
	virtual void Deserialize(char* buffer);
};