#pragma once

#include "ModbusMessageTCP.h"

class ReadDescreteInputsMessage : ModbusMessageTCP
{
private:
	unsigned short startingAddress;
	unsigned short quantityOfCoils;

	unsigned short byteCount;
	char* coilStatus;
public:
	ReadDescreteInputsMessage();
	ReadDescreteInputsMessage(char* bytes);
	virtual char* Serialize();
	virtual void Deserialize(char* msg);
};
