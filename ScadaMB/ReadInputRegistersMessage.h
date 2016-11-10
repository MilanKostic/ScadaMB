#pragma once

#include "ModbusMessageTCP.h"
#include "ReadHoldingRegistersMessage.h"

class ReadInputRegistersMessage : public ReadHoldingRegistersMessage
{
private:
public:
	ReadInputRegistersMessage(unsigned short startingAddress, unsigned short quantityOfRegisters);
	ReadInputRegistersMessage();
	ReadInputRegistersMessage(char* buffer);
};