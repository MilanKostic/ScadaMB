#pragma once

#include "ModbusMessageTCP.h"
#include "WriteSingleCoilMessage.h"

class WriteSingleRegisterMessage : public WriteSingleCoilMessage
{
private:
public:
	WriteSingleRegisterMessage();
	WriteSingleRegisterMessage(char* buffer);
	WriteSingleRegisterMessage(unsigned short outputAddress, unsigned short outputValue);
};