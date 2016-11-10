#include "DigitalDevice.h"

DigitalDevice::DigitalDevice(string name, bool readOnly, unsigned int inAddress[2], unsigned int outAddress[2], PointState state, PointStatus status, PointState command/*, RTU *rtu*/)
{
	this->name = name;
	this->isReadOnly = readOnly;
	this->inAddress[0] = inAddress[0];
	this->inAddress[1] = inAddress[1];
	this->outAddress[0] = outAddress[0];
	this->outAddress[1] = outAddress[1];
	this->state = state;
	this->status = status;
	this->command = command;
	//this->rtu = rtu;
}


void DigitalDevice::SetCommand(PointState value)
{
	command = value;
}

void DigitalDevice::SetState(PointState value)
{
	state = value;
}

void DigitalDevice::SetStatus(PointStatus value)
{
	status = value;
}

string DigitalDevice::GetName()
{
	return string();
}

bool DigitalDevice::IsReadOnly()
{
	return isReadOnly;
}

unsigned int DigitalDevice::GetInAddress()
{
	return *inAddress;
}

unsigned int DigitalDevice::GetOutAddress()
{
	return *outAddress;
}

PointState DigitalDevice::GetPointState()
{
	return state;
}

PointStatus DigitalDevice::GetPointStatus()
{
	return status;
}
/*
RTU* DigitalDevice::GetRTU()
{
	return rtu;
}*/

PointState DigitalDevice::GetCommand()
{
	return command;
}
