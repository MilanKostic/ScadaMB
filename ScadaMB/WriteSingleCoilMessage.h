#pragma once

#include "ModbusMessageTCP.h"
#include "PointStates.h"

class WriteSingleCoilMessage : public ModbusMessageTCP
{
protected:
	unsigned short outputAddress;
	char outputValue[2];
public:
	WriteSingleCoilMessage();
	WriteSingleCoilMessage(char* buffer);
	WriteSingleCoilMessage(unsigned short outputAddress, PointState outputValue);
	virtual char* Serialize();
	virtual void Deserialize(char* buffer);
};