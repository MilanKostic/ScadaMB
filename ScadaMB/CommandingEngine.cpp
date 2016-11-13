#include "CommandingEngine.h"

CommandingEngine* CommandingEngine::instance = NULL;

CommandingEngine::CommandingEngine()
{
}

CommandingEngine::CommandingEngine(SOCKET socket)
{
	scadaSocket = socket;
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
	switch(message[2]){
		case '1': { ModbusDriverTCP::Instance()->SendModbusMessage(NULL /*Soket od RTU - a*/ ,
			new WriteSingleCoilMessage(PointAddress::dozvolaPraznjenjaMjesalice, *(int*)(message+2))); break; }
	}
}

void CommandingEngine::StartIncrement100UnitPS()
{
	for each (pair<int, RTU*> rtu in RTDB::Instance()->GetRemotes())
	{
		std::thread t1(IncrementForOneRTU, rtu.second);
	}
}

void IncrementForOneRTU(RTU *rtu) {
	while (true) {
		if (rtu->GetDigitalDevices().find(PointAddress::ventilVode)->second->GetPointState() == PointState::On) {
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a*/,
				new WriteSingleRegisterMessage(PointAddress::kolicinaVodeOut, 100));
		}
		if (rtu->GetDigitalDevices().find(PointAddress::ventilPeska)->second->GetPointState() == PointState::On) {
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a*/,
				new WriteSingleRegisterMessage(PointAddress::kolicinaPijeskaOut, 100));
		}
		if (rtu->GetDigitalDevices().find(PointAddress::ventilSljunka)->second->GetPointState() == PointState::On) {
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a*/,
				new WriteSingleRegisterMessage(PointAddress::kolicinaSljunkaOut, 100));
		}
		Sleep(1000);
	}
}
