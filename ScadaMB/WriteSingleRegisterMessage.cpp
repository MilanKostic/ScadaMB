#include "WriteSingleRegisterMessage.h"
#include "SocketWrapper.h"

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
{
	this->functionCode = ModbusMessageTypes::WRITE_SINGLE_REGISTER;
	this->header.transactionIdentifier = htons(0x0001);
	this->header.protocolIdentifier = htons(0x0000);
	this->header.length = htons(6);
	this->header.unitIdentifier = 0x01;
	this->outputAddress = htons(outputAddress);
	*(unsigned short*)this->outputValue = htons(outputValue);
	this->messageLength = this->headerLength + 5;
}
