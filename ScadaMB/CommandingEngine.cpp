#include "CommandingEngine.h"

CommandingEngine* CommandingEngine::instance = NULL;

CommandingEngine::CommandingEngine()
{
}

CommandingEngine * CommandingEngine::Instance()
{
	if (instance == NULL) {
		instance = new CommandingEngine();
	}
	return instance;
}

void CommandingEngine::CreateCommand(char * message)
{
	/*
	ModbusMessageTCP msg;
	switch(message[2]){
		case:'1'
		case:'2' msg = WriteHoldMessage...
	}
	ModbusDriverTCP::Instace()->Send(msg...502)
	*/
}

void CommandingEngine::Increment100UnitPS()
{
	/*ovo ce se pozivati unutar posebne niti
	while(1){
		if(!RTDB::Intance()->VentilVode()){
			ModbusMessageTCP msg;
			ModbusDriverTCP::Instace()->Send(msg...502)
		}
		if(!RTDB::Intance()->VentilPijeska()){
		ModbusMessageTCP msg;
		ModbusDriverTCP::Instace()->Send(msg...502)
		}
		if(!RTDB::Intance()->VentilSljunka()){
		ModbusMessageTCP msg;
		ModbusDriverTCP::Instace()->Send(msg...502)
		}
	}
	*/
}
