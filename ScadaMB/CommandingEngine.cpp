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
		case '1': 
		{
			RTU* rtu = RTDB::Instance()->GetRTU(PointAddress::rtuId);
			for each(std::pair<unsigned short, DigitalDevice*> device in rtu->GetDigitalDevices())
			{
				if (device.second->GetOutAddress() == PointAddress::dozvolaPraznjenjaMjesalice)
				{
					device.second->SetCommand((PointState)*(int*)(message + 2)); 
					break;
				}
			}
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(),
			new WriteSingleCoilMessage(PointAddress::dozvolaPraznjenjaMjesalice, (PointState)*(int*)(message+2)));
			break; 
		}
	}
}

void CommandingEngine::StartIncrement100UnitPS()
{
	for each (pair<int, RTU*> rtu in RTDB::Instance()->GetRemotes())
	{
		std::thread(IncrementForOneRTU, rtu.second).detach();
	}
}

//Uvecavanje/smanjivanje sirovine na odredjenom analognom izlazu sa adresom outAnalogAddress
void IncHelp(RTU* rtu, unsigned short outAnalogAddress, unsigned short digitalDeviceId)
{
	if (rtu->GetDigitalDevices().find(digitalDeviceId)->second->GetPointState() == PointState::On) 
	{
		ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(),
			new WriteSingleRegisterMessage(outAnalogAddress, rtu->GetIncrementValue(outAnalogAddress)));
	}
	else
	{
		short decrementValue = rtu->GetDecrementValue(outAnalogAddress);
		if (decrementValue >= 0)
		{
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(),
				new WriteSingleRegisterMessage(outAnalogAddress, decrementValue));
		}
	}
}

void IncrementForOneRTU(RTU *rtu) {
	while (true) {
		/*if (rtu->GetDigitalDevices().find(PointAddress::ventilVode)->second->GetPointState() == PointState::On) {
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a,
				new WriteSingleRegisterMessage(PointAddress::kolicinaVodeOut, rtu->GetIncrementValue(PointAddress::kolicinaVodeOut)));
		}
		if (rtu->GetDigitalDevices().find(PointAddress::ventilPeska)->second->GetPointState() == PointState::On) {
			WriteSingleRegisterMessage* response = (WriteSingleRegisterMessage*)ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a,
				new WriteSingleRegisterMessage(PointAddress::kolicinaPijeskaOut, rtu->GetIncrementValue(PointAddress::kolicinaPijeskaOut)));
		}
		if (rtu->GetDigitalDevices().find(PointAddress::ventilSljunka)->second->GetPointState() == PointState::On) {
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket()/*Soket od RTU-a,
				new WriteSingleRegisterMessage(PointAddress::kolicinaSljunkaOut, rtu->GetIncrementValue(PointAddress::kolicinaSljunkaOut)));
		}
		*/
		IncHelp(rtu, PointAddress::kolicinaVodeOut, PointAddress::ventilVode);
		IncHelp(rtu, PointAddress::kolicinaPijeskaOut, PointAddress::ventilPeska);
		IncHelp(rtu, PointAddress::kolicinaSljunkaOut, PointAddress::ventilSljunka);

		if (rtu->GetAnalogOutoputList().find(PointAddress::kolicinaVodeOut)->second->GetRaw() == 0 && rtu->GetAnalogOutoputList().find(PointAddress::kolicinaPijeskaOut)->second->GetRaw() == 0 && rtu->GetAnalogOutoputList().find(PointAddress::kolicinaSljunkaOut)->second->GetRaw() == 0)
		{
			// Postaviti mjesalicu da je prazna
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(),
				new WriteSingleCoilMessage(PointAddress::stanjeMjesalice, PointState::Off));
		}
		else if (rtu->GetDigitalDevices().find(PointAddress::stanjeMjesaliceId)->second->GetPointState() == PointState::Off)
		{
			ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(),
				new WriteSingleCoilMessage(rtu->GetDigitalDevices().find(PointAddress::stanjeMjesaliceId)->second->GetOutAddress(), PointState::On));
		}

		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}
