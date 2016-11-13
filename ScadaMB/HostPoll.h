#pragma once
#include "ModbusMessageTCP.h"

/*
	Ova klasa enkapsulira poslatu poruku i primljenu poruku sa rtu,
	sto je potrebno DataProcessingEngine-u za obradu, tj crunching
*/
class HostPoll
{
private:
	ModbusMessageTCP* request;
	ModbusMessageTCP* response;
public:
	HostPoll(ModbusMessageTCP* req, ModbusMessageTCP* resp)
	{
		this->request = req;
		this->response = resp;
	}
	ModbusMessageTCP* GetRequest()
	{
		return request;
	}
	ModbusMessageTCP* GetResponse()
	{
		return response;
	}
};
