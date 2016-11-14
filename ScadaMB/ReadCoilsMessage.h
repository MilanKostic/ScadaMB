#pragma once

#include "ModbusMessageTCP.h"
#include "RTDB.h"
#include "RTU.h"

class ReadCoilsMessage : public ModbusMessageTCP
{
private:
	unsigned short startingAddress;
	unsigned short quantityOfCoils;

	unsigned short byteCount;
	char* coilStatus = nullptr;
public:
	ReadCoilsMessage(unsigned short startingAddress, unsigned short numberOfCoils);
	ReadCoilsMessage();
	ReadCoilsMessage(char* bytes);
	virtual char* Serialize();
	virtual void Deserialize(char* msg);
	void SetStartingAddress(unsigned short sa);
	void setQuantityOfCoils(unsigned short qc);
	unsigned short GetQuantityOfCoils();
	bool GetBit(char c, unsigned short position);
	unsigned short GetStartingAddress();
	virtual void Crunch(int rtuId, ModbusMessageTCP* req);
};
