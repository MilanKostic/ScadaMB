#pragma once

#include <iostream>
#include "ModbusDriverTCP.h"

class CommandingEngine {
private:
	static CommandingEngine *instance;
	CommandingEngine();
public:
	static CommandingEngine *Instance();
	void CreateCommand(char *message);

	void Increment100UnitPS();
};