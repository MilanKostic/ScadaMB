#include "ReadCoilsMessage.h"
#include <string>
#include "Socket.h"

ReadCoilsMessage::ReadCoilsMessage(unsigned short length, unsigned short startingAddress, unsigned short numberOfCoils)
{
	this->functionCode = ModbusMessageTypes::READ_COILS;
	this->header.transactionIdentifier = htons(0x0001);
	this->header.protocolIdentifier = htons(0x0000);
	this->header.length = htons(length);
	this->header.unitIdentifier = 0x01;
	this->startingAddress = startingAddress;
	this->quantityOfCoils = numberOfCoils;
	this->messageLength = this->headerLength + this->header.length - 1;
}

ReadCoilsMessage::ReadCoilsMessage()
{
	this->functionCode = ModbusMessageTypes::READ_COILS;
}

ReadCoilsMessage::ReadCoilsMessage(char* bytes) : ModbusMessageTCP(bytes)
{
	this->functionCode = ModbusMessageTypes::READ_COILS;
	this->Deserialize(bytes);
}

char* ReadCoilsMessage::Serialize()
{
	char* retValue = new char(messageLength);

	*(Header*)&retValue[0] = header;
	retValue[headerLength] = functionCode;
	*(unsigned short*)&retValue[headerLength + 1] = htons(startingAddress);
	*(unsigned short*)&retValue[headerLength + 3] = htons(quantityOfCoils);

	return retValue;
}

void ReadCoilsMessage::Deserialize(char* msg)
{
	ModbusMessageTCP::Deserialize(msg);
	this->functionCode = msg[headerLength];
	char temp[2];
	temp[0] = msg[headerLength + 1];
	temp[1] = 0;
	memcpy(&this->byteCount, temp, 2);
	this->coilStatus = new char(this->byteCount);
	memcpy(this->coilStatus, &msg[headerLength + 2], this->byteCount);
	this->messageLength = headerLength + this->header.length - 1;
}

void ReadCoilsMessage::SetStartingAddress(unsigned short sa)
{
	this->startingAddress = sa;
}

void ReadCoilsMessage::setQuantityOfCoils(unsigned short qc)
{
	this->quantityOfCoils = qc;
}

