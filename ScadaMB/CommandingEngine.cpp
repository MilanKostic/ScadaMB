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

void CommandingEngine::CreateCommand(char * message, SocketStruct* socket)
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
					device.second->SetCommandingProgress(true);
					break;
				}
			}
			WriteSingleCoilMessage* req = new WriteSingleCoilMessage(PointAddress::dozvolaPraznjenjaMjesalice, (PointState)*(int*)(message + 2));
			ModbusMessageTCP* resp = ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(), req);
			
			char* success = "KOMANDA - POSLATA\n\0";
			char* error = "GRESKA U SLANJU KOMANDE\n\0";
			if (req->GetFunctionCode() == resp->GetFunctionCode())
			{
				SocketWrapper::Instance()->Send(socket, success, strlen(success) + 1);
			}
			else
			{
				SocketWrapper::Instance()->Send(socket, error, strlen(error) + 1);
			}
			delete req;
			delete resp;

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
	ModbusMessageTCP* req = NULL;
	ModbusMessageTCP* resp = NULL;
	if (rtu->GetDigitalDevices().find(digitalDeviceId)->second->GetPointState() == PointState::On) 
	{
		req = new WriteSingleRegisterMessage(outAnalogAddress, rtu->GetIncrementValue(outAnalogAddress));
		resp = ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(), req);
	}
	else
	{
		short decrementValue = rtu->GetDecrementValue(outAnalogAddress);
		if (decrementValue >= 0)
		{
			req = new WriteSingleRegisterMessage(outAnalogAddress, decrementValue);
			resp = ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(), req);
		}
	}
	delete req;
	delete resp;
}

void IncrementForOneRTU(RTU *rtu) {
	
	ModbusMessageTCP* req = NULL;
	ModbusMessageTCP* resp = NULL;

	while (true) {
		IncHelp(rtu, PointAddress::kolicinaVodeOut, PointAddress::ventilVode);
		IncHelp(rtu, PointAddress::kolicinaPijeskaOut, PointAddress::ventilPeska);
		IncHelp(rtu, PointAddress::kolicinaSljunkaOut, PointAddress::ventilSljunka);

		if (rtu->GetAnalogOutoputList().find(PointAddress::kolicinaVodeOut)->second->GetRaw() == 0 && rtu->GetAnalogOutoputList().find(PointAddress::kolicinaPijeskaOut)->second->GetRaw() == 0 && rtu->GetAnalogOutoputList().find(PointAddress::kolicinaSljunkaOut)->second->GetRaw() == 0)
		{
			// Postaviti mjesalicu da je prazna
			rtu->GetDigitalDevices().find(PointAddress::stanjeMjesaliceId)->second->SetCommand(PointState::Off);
			req = new WriteSingleCoilMessage(PointAddress::stanjeMjesalice, PointState::Off);
			resp = ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(), req);
		}
		else if (rtu->GetDigitalDevices().find(PointAddress::stanjeMjesaliceId)->second->GetPointState() != PointState::On)
		{
			rtu->GetDigitalDevices().find(PointAddress::stanjeMjesaliceId)->second->SetCommand(PointState::On);
			req = new WriteSingleCoilMessage(rtu->GetDigitalDevices().find(PointAddress::stanjeMjesaliceId)->second->GetOutAddress(), PointState::On);
			resp = ModbusDriverTCP::Instance()->SendModbusMessage(rtu->GetSocket(), req);
		}
		delete req;
		delete resp;
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}
