#include "WriteSingleCoilMessage.h"
#include "Socket.h"

WriteSingleCoilMessage::WriteSingleCoilMessage()
{
	this->functionCode = ModbusMessageTypes::WRITE_SINGLE_COIL;
}

WriteSingleCoilMessage::WriteSingleCoilMessage(char* buffer)
{
	this->functionCode = ModbusMessageTypes::WRITE_SINGLE_COIL;
	this->Deserialize(buffer);
}

WriteSingleCoilMessage::WriteSingleCoilMessage(unsigned short outputAddress, PointState outputValue)
{
	this->functionCode = ModbusMessageTypes::WRITE_SINGLE_COIL;
	this->header.transactionIdentifier = htons(0x0001);
	this->header.protocolIdentifier = htons(0x0000);
	this->header.length = htons(6);
	this->header.unitIdentifier = 0x01;
	this->outputAddress = htons(outputAddress);
	*(unsigned short*)this->outputValue = htons(outputValue == PointState::Off ? 0x0000 : 0xff00);
	this->messageLength = this->headerLength + 5;
}

char * WriteSingleCoilMessage::Serialize()
{
	char* retValue = new char[this->messageLength];
	
	*(Header*)&retValue[0] = this->header;
	retValue[headerLength] = this->functionCode;
	*(unsigned short*)&retValue[headerLength + 1] = this->outputAddress;
	memcpy(&retValue[headerLength + 3], this->outputValue, 2);

	return retValue;
}

void WriteSingleCoilMessage::Deserialize(char* buffer)
{
	ModbusMessageTCP::Deserialize(buffer);
	this->functionCode = buffer[this->headerLength];
	this->outputAddress = ntohs(*(unsigned short*)&buffer[this->headerLength + 1]);
	memcpy(this->outputValue, &buffer[this->headerLength + 3], 2);
}
