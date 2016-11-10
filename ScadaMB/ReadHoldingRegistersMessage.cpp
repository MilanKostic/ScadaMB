#include "ReadHoldingRegistersMessage.h"
#include <string>
#include "Socket.h"

ReadHoldingRegistersMessage::ReadHoldingRegistersMessage(unsigned short startingAddress, unsigned short quantityOfRegisters)
{
	this->functionCode = ModbusMessageTypes::READ_HOLDING_REGISTERS;
	this->header.transactionIdentifier = htons(0x0001);
	this->header.protocolIdentifier = htons(0x0000);
	this->header.length = htons(6);
	this->header.unitIdentifier = 0x01;
	this->startingAddress = startingAddress;
	this->quantityOfRegisters = quantityOfRegisters;
	this->messageLength = this->headerLength + 5;
}

ReadHoldingRegistersMessage::ReadHoldingRegistersMessage()
{
	this->functionCode = ModbusMessageTypes::READ_HOLDING_REGISTERS;
}

ReadHoldingRegistersMessage::ReadHoldingRegistersMessage(char* bytes) : ModbusMessageTCP(bytes)
{
	this->functionCode = ModbusMessageTypes::READ_HOLDING_REGISTERS;
	this->Deserialize(bytes);
}

char* ReadHoldingRegistersMessage::Serialize()
{
	char* retValue = new char(this->messageLength);
	
	*(Header*)&retValue[0] = this->header;
	retValue[headerLength] = this->functionCode;
	*(unsigned short*)&retValue[headerLength + 1] = htons(this->startingAddress);
	*(unsigned short*)&retValue[headerLength + 3] = htons(this->quantityOfRegisters);

	return retValue;
}

void ReadHoldingRegistersMessage::Deserialize(char * buffer)
{
	ModbusMessageTCP::Deserialize(buffer);
	this->functionCode = buffer[headerLength];
	char temp[2];
	temp[0] = buffer[headerLength + 1];
	temp[1] = 0;
	memcpy(&this->byteCount, temp, 2);
	this->registerValue = new unsigned short(this->byteCount / 2);
	memcpy(this->registerValue, &buffer[headerLength + 2], sizeof(char) * this->byteCount);
	for (int i = 0; i < this->byteCount / 2; i++)
	{
		this->registerValue[i] = ntohs(this->registerValue[i]);
	}
	this->messageLength = headerLength + this->header.length - 1;
}
