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
}

int ModbusMessageTCP::GetMessageLength()
{
	return messageLength;
}
