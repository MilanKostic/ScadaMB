#pragma once

#include "ModbusMessageTCP.h"

class WriteSingleCoilMessage : public ModbusMessageTCP
{
private:
	unsigned short outputAddress;
	char outputValue[2];
public:
	WriteSingleCoilMessage();
	WriteSingleCoilMessage(char* buffer);
	WriteSingleCoilMessage(unsigned short outputAddress, unsigned short outputValue);
	virtual char* Serialize();
	virtual void Deserialize(char* buffer);
};