#include "WriteSingleRegisterMessage.h"

WriteSingleRegisterMessage::WriteSingleRegisterMessage()
{
	this->functionCode = ModbusMessageTypes::WRITE_SINGLE_REGISTER;
}

WriteSingleRegisterMessage::WriteSingleRegisterMessage(char * buffer)
{
	this->functionCode = ModbusMessageTypes::WRITE_SINGLE_REGISTER;
	this->Deserialize(buffer);
}

WriteSingleRegisterMessage::WriteSingleRegisterMessage(unsigned short outputAddress, unsigned short outputValue)
	: WriteSingleCoilMessage(outputAddress, outputValue)
{
	this->functionCode = ModbusMessageTypes::WRITE_SINGLE_REGISTER;
}
