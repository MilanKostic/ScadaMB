#include "PollEngine.h"
#include "ReadHoldingRegistersMessage.h"
#include "ReadInputRegistersMessage.h"
#include "ReadDescreteInputsMessage.h"
#include "ReadCoilsMessage.h"
#include "ModbusDriverTCP.h"

PollEngine::PollEngine()
{
}

void ProcessThread(DataProcessingEngine* dpe)
{
	dpe->Process();
}

void PollEngine::Poll()
{
	for each(std::pair<int, RTU*> rtu in RTDB::Instance()->GetRemotes())
	{
		for each(std::pair<unsigned short, AnalogInput*> analogInput in rtu.second->GetAnalogInputList())
		{
			ReadInputRegistersMessage* reqInputReg = new ReadInputRegistersMessage(analogInput.second->GetAddress(), 1);
			ReadInputRegistersMessage* respInputReg = (ReadInputRegistersMessage*)ModbusDriverTCP::Instance()->SendModbusMessage(rtu.second->GetSocket(), reqInputReg);
			if(reqInputReg->GetFunctionCode() == respInputReg->GetFunctionCode())
				this->dataProcessingEngine.AddHostPoll(rtu.second->GetID(), new HostPoll(reqInputReg, respInputReg));
		}
		for each(std::pair<unsigned short, AnalogOutput*> analogOutput in rtu.second->GetAnalogOutoputList())
		{
			ReadHoldingRegistersMessage* reqHoldingReg = new ReadHoldingRegistersMessage(analogOutput.second->GetAddress(), 1);
			ReadHoldingRegistersMessage* respHoldingReg = (ReadInputRegistersMessage*)ModbusDriverTCP::Instance()->SendModbusMessage(rtu.second->GetSocket(), reqHoldingReg);
			if(reqHoldingReg->GetFunctionCode() == respHoldingReg->GetFunctionCode())
				this->dataProcessingEngine.AddHostPoll(rtu.second->GetID(), new HostPoll(reqHoldingReg, respHoldingReg));
		}
		for each(std::pair<unsigned short, DigitalDevice*> digitalDevice in rtu.second->GetDigitalDevices())
		{
			ModbusMessageTCP* reqMessage = new ReadDescreteInputsMessage(digitalDevice.second->GetInAddresses()[0], 2);
			ModbusMessageTCP* respMessage = ModbusDriverTCP::Instance()->SendModbusMessage(rtu.second->GetSocket(), reqMessage);
			if(reqMessage->GetFunctionCode() == respMessage->GetFunctionCode())
				this->dataProcessingEngine.AddHostPoll(rtu.second->GetID(), new HostPoll(reqMessage, respMessage));
		}
	}
	//thread(&ProcessThread, &this->dataProcessingEngine).detach();
	this_thread::sleep_for(chrono::milliseconds(this->sendInterval));
}

DataProcessingEngine * PollEngine::GetDPE()
{
	return &dataProcessingEngine;
}

void PollThread(PollEngine* pollEngine)
{
	while (true)
	{
		pollEngine->Poll();
	}
}

