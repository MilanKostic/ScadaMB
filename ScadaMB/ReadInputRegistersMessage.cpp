#include "ReadInputRegistersMessage.h"

ReadInputRegistersMessage::ReadInputRegistersMessage(unsigned short startingAddress, unsigned short quantityOfRegisters)
	: ReadHoldingRegistersMessage(startingAddress, quantityOfRegisters)
{
	this->functionCode = ModbusMessageTypes::READ_INPUT_REGISTERS;
}

ReadInputRegistersMessage::ReadInputRegistersMessage()
{
	this->functionCode = ModbusMessageTypes::READ_INPUT_REGISTERS;
}

ReadInputRegistersMessage::ReadInputRegistersMessage(char * buffer)
{
	this->functionCode = ModbusMessageTypes::READ_INPUT_REGISTERS;
	this->Deserialize(buffer);
}
