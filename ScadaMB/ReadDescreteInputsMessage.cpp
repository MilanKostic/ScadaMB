#include "ReadDescreteInputsMessage.h"
#include <string>

ReadDescreteInputsMessage::ReadDescreteInputsMessage()
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}

ReadDescreteInputsMessage::ReadDescreteInputsMessage(char* bytes) : ModbusMessageTCP(bytes)
{
	this->functionCode = ModbusMessageTypes::READ_DESCRETE_INPUTS;
}

char* ReadDescreteInputsMessage::Serialize()
{
	char* retValue = new char(messageLength);

	*(Header*)&retValue[0] = header;
	retValue[headerLength] = functionCode;
	*(unsigned short*)&retValue[headerLength + 1] = startingAddress;
	*(unsigned short*)&retValue[headerLength + 2] = quantityOfCoils;

	return retValue;
}

void ReadDescreteInputsMessage::Deserialize(char* msg)
{
	ModbusMessageTCP::Deserialize(msg);
	this->functionCode = msg[headerLength];
	this->byteCount = *(unsigned short*)&msg[headerLength + 1];
	this->coilStatus = new char(this->byteCount);
	memcpy(this->coilStatus, &msg[headerLength + 2], this->byteCount);
	this->messageLength = headerLength + this->byteCount - 1;
}
