#include "ReadDescreteInputsMessage.h"
#include <string>

ReadDescreteInputsMessage::ReadDescreteInputsMessage(unsigned short length, unsigned short startingAddress, unsigned short quantityOfInputs)
	: ReadCoilsMessage(length, startingAddress, quantityOfInputs)
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}

ReadDescreteInputsMessage::ReadDescreteInputsMessage()
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}

ReadDescreteInputsMessage::ReadDescreteInputsMessage(char* bytes)
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}
