#include "ModbusMessageTCP.h"

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
	header.transactionIdentifier = *(unsigned short*)&msg[0];
	header.protocolIdentifier = *(unsigned short*)&msg[2];
	header.length = *(unsigned short*)&msg[4];
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
