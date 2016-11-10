#pragma once

#include <iostream>
#include "ModbusDriverTCP.h"
#include "WriteSingleCoilMessage.h"

class CommandingEngine {
private:
	SOCKET scadaSocket;
	static CommandingEngine *instance;
	CommandingEngine(SOCKET scadaSocket);
	CommandingEngine();
public:
	static CommandingEngine *Instance();
	void CreateCommand(char *message);

	void Increment100UnitPS();
};