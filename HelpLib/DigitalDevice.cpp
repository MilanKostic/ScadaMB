#include "DigitalDevice.h"

DigitalDevice::DigitalDevice(unsigned short id, string name, bool readOnly, unsigned short inAddr1, unsigned short inAddr2, unsigned short outAddress, PointState state, PointStatus status, PointState command/*, RTU *rtu*/)
{
	this->id = id;
	this->name = name;
	this->isReadOnly = readOnly;
	this->inAddresses[0] = inAddr1;
	this->inAddresses[1] = inAddr2;
	this->outAddress = outAddress;
	this->state = state;
	this->status = status;
	this->command = command;
	this->commandingProgress = false;
	//this->rtu = rtu;
}


DigitalDevice::DigitalDevice(unsigned short id, string name, bool readOnly, unsigned short inAddr1, unsigned short inAddr2, unsigned short outAddress)
{
	this->id = id;
	this->name = name;
	this->isReadOnly = readOnly;
	this->inAddresses[0] = inAddr1;
	this->inAddresses[1] = inAddr2;
	this->outAddress = outAddress;
	this->status = PointStatus::OnScan;
	this->state = PointState::Off;
	this->command = PointState::Off;
	this->commandingProgress = false;
}

void DigitalDevice::SetCommand(PointState value)
{
	this->command = value;
}

void DigitalDevice::SetState(PointState value)
{
	this->state = value;
}

void DigitalDevice::SetStatus(PointStatus value)
{
	this->status = value;
}

string DigitalDevice::GetName()
{
	return this->name;
}

bool DigitalDevice::IsReadOnly()
{
	return isReadOnly;
}

unsigned short* DigitalDevice::GetInAddresses()
{
	return inAddresses;
}

unsigned short DigitalDevice::GetOutAddress()
{
	return outAddress;
}

unsigned short DigitalDevice::GetId()
{
	return this->id;
}

PointState DigitalDevice::GetPointState()
{
	return this->state;
}

PointStatus DigitalDevice::GetPointStatus()
{
	return this->status;
}
/*
RTU* DigitalDevice::GetRTU()
{
	return rtu;
}*/

PointState DigitalDevice::GetCommand()
{
	return this->command;
}

bool DigitalDevice::GetCommandingProgress()
{
	return this->commandingProgress;
}

void DigitalDevice::SetCommandingProgress(bool value)
{
	this->commandingProgress = value;
}
