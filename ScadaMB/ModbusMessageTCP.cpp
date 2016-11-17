#include "ModbusMessageTCP.h"
#include "SocketWrapper.h"

ModbusMessageTCP::ModbusMessageTCP() {}

ModbusMessageTCP::ModbusMessageTCP(char* bytes)
{
	this->Deserialize(bytes);
}

char* ModbusMessageTCP::Serialize()
{
	return nullptr;
}

void ModbusMessageTCP::Deserialize(char* msg)
{
	header.transactionIdentifier = ntohs(*(unsigned short*)&msg[0]);
	header.protocolIdentifier = ntohs(*(unsigned short*)&msg[2]);
	header.length = ntohs(*(unsigned short*)&msg[4]);
	header.unitIdentifier = msg[6];
}

int ModbusMessageTCP::GetMessageLength()
{
	return messageLength;
}

void ModbusMessageTCP::SetFunctionCode(ModbusMessageTypes code)
{
	this->functionCode = code;
}

void ModbusMessageTCP::SetHeader(Header header)
{
	this->header.length = header.length;
	this->header.protocolIdentifier = header.protocolIdentifier;
	this->header.transactionIdentifier = header.transactionIdentifier;
	this->header.unitIdentifier = header.unitIdentifier;
}

void ModbusMessageTCP::SetMessageLength(int msgLen)
{
	this->messageLength = msgLen;
}

void ModbusMessageTCP::Crunch(int rtuId, ModbusMessageTCP* req)
{
}

char ModbusMessageTCP::GetFunctionCode()
{
	return this->functionCode;
}
