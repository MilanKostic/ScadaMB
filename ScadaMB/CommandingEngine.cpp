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
	switch(message[1]){
	case '1': { ModbusDriverTCP::Instance()->SendModbusMessage(RTDB::Instance()->GetRTU(PointAddress::rtuId)->GetSocket() /*Soket od RTU - a*/ ,
			new WriteSingleCoilMessage(PointAddress::dozvolaPraznjenjaMjesalice, (PointState)*(int*)(message+2))); break; }
	}
}

void CommandingEngine::StartIncrement100UnitPS()
{
	for each (pair<int, RTU*> rtu in RTDB::Instance()->GetRemotes())
	{
		std::thread(IncrementForOneRTU, rtu.second).detach();
	}
}

void IncrementForOneRTU(RTU *rtu) {
	while (true) {
		if (rtu->GetDigitalDevices().find(PointAddress::ventilVode)->second->GetPointState() == PointState::On) {
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a*/,
				new WriteSingleRegisterMessage(PointAddress::kolicinaVodeOut, rtu->GetIncrementValue(PointAddress::kolicinaVodeOut)));
		}
		if (rtu->GetDigitalDevices().find(PointAddress::ventilPeska)->second->GetPointState() == PointState::On) {
			WriteSingleRegisterMessage* response = (WriteSingleRegisterMessage*)ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a*/,
				new WriteSingleRegisterMessage(PointAddress::kolicinaPijeskaOut, rtu->GetIncrementValue(PointAddress::kolicinaPijeskaOut)));
		}
		if (rtu->GetDigitalDevices().find(PointAddress::ventilSljunka)->second->GetPointState() == PointState::On) {
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a*/,
				new WriteSingleRegisterMessage(PointAddress::kolicinaSljunkaOut, rtu->GetIncrementValue(PointAddress::kolicinaSljunkaOut)));
		}
		
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}
