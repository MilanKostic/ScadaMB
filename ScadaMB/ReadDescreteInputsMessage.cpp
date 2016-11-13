#include "ReadDescreteInputsMessage.h"
#include <string>

ReadDescreteInputsMessage::ReadDescreteInputsMessage(unsigned short startingAddress, unsigned short quantityOfInputs)
	: ReadCoilsMessage(startingAddress, quantityOfInputs)
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}

ReadDescreteInputsMessage::ReadDescreteInputsMessage()
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}

ReadDescreteInputsMessage::ReadDescreteInputsMessage(char* bytes)
	: ReadCoilsMessage(bytes)
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}
