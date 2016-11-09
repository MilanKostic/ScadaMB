#pragma once

#include "ModbusMessageTCP.h"
#include "ReadCoilsMessage.h"

class ReadDescreteInputsMessage : public ReadCoilsMessage
{
private:
	unsigned short startingAddress;
	unsigned short quantityOfCoils;

	char byteCount;
	char* coilStatus;
public:
	ReadDescreteInputsMessage(unsigned short length, unsigned short startingAddress, unsigned short quantityOfInputs);
	ReadDescreteInputsMessage();
	ReadDescreteInputsMessage(char* bytes);
};
