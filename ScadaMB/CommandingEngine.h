#pragma once

#include <iostream>
#include "ModbusDriverTCP.h"
#include "WriteSingleCoilMessage.h"
#include "WriteSingleRegisterMessage.h"
#include "PointAddress.h"
#include <map>
#include "RTDB.h"
#include <thread>

class CommandingEngine {
private:
	SOCKET scadaSocket;
	static CommandingEngine *instance;
	CommandingEngine(SOCKET scadaSocket);
	CommandingEngine();
public:
	static CommandingEngine *Instance();
	void CreateCommand(char *message);

	void StartIncrement100UnitPS();
};
void IncrementForOneRTU(RTU *rtu);