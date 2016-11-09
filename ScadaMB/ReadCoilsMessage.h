#pragma once

#include "ModbusMessageTCP.h"

class ReadCoilsMessage : public ModbusMessageTCP
{
private:
	unsigned short startingAddress;
	unsigned short quantityOfCoils;

	unsigned short byteCount;
	char* coilStatus;
public:
	ReadCoilsMessage(unsigned short length, unsigned short startingAddress, unsigned short numberOfCoils);
	ReadCoilsMessage();
	ReadCoilsMessage(char* bytes);
	virtual char* Serialize();
	virtual void Deserialize(char* msg);
	void SetStartingAddress(unsigned short sa);
	void setQuantityOfCoils(unsigned short qc);
};
