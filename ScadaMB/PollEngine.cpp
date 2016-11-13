#include "PollEngine.h"
#include "ReadHoldingRegistersMessage.h"
#include "ReadInputRegistersMessage.h"
#include "ModbusDriverTCP.h"

PollEngine::PollEngine()
{
}

void PollEngine::Poll()
{
	for each(std::pair<int, RTU*> rtu in RTDB::Instance()->GetRemotes())
	{
		for each(std::pair<unsigned short, AnalogInput*> analogInput in rtu.second->GetAnalogInputList())
		{
			ReadInputRegistersMessage* reqInputReg = new ReadInputRegistersMessage(analogInput.second->GetAddress(), 1);
			ReadInputRegistersMessage* respInputReg = (ReadInputRegistersMessage*)ModbusDriverTCP::Instance()->SendModbusMessage(rtu.second->GetSocket(), reqInputReg);
			this->dataProcessingEngine.AddHostPoll(rtu.second->GetID(), new HostPoll(reqInputReg, respInputReg));
		}
		// Isto treba uraditi za digitalne uredjaje
	}
	thread(&ProcessThread, &this->dataProcessingEngine);
	this_thread::sleep_for(chrono::milliseconds(this->sendInterval));
}

void PollThread()
{
	PollEngine pollEngine;
	while (true)
	{
		pollEngine.Poll();
	}
}

void ProcessThread(DataProcessingEngine* dpe)
{
	dpe->Process();
}
