#pragma once

#include "ModbusMessageTCP.h"
#include "ReadCoilsMessage.h"

class ReadDescreteInputsMessage : public ReadCoilsMessage
{
private:
public:
	ReadDescreteInputsMessage(unsigned short startingAddress, unsigned short quantityOfInputs);
	ReadDescreteInputsMessage();
	ReadDescreteInputsMessage(char* bytes);
};
