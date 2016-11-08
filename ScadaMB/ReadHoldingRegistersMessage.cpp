#include "ReadHoldingRegistersMessage.h"

ReadHoldingRegistersMessage::ReadHoldingRegistersMessage()
{
	this->functionCode = ModbusMessageTypes::READ_HOLDING_REGISTERS;
}

ReadHoldingRegistersMessage::ReadHoldingRegistersMessage(char* bytes) : ModbusMessageTCP(bytes)
{
	this->functionCode = ModbusMessageTypes::READ_HOLDING_REGISTERS;
}

char* ReadHoldingRegistersMessage::Serialize()
{
	return nullptr;
}

void ReadHoldingRegistersMessage::Deserialize(char * buffer)
{
	ModbusMessageTCP::Deserialize(buffer);
}
