#include "Alarm.h"

Alarm::Alarm(RTU * rtuDev, DigitalDevice * digitalDev)
{
	rtuDevice = rtuDev;
	digitalDevice = digitalDev;
	this->accepted = false;
	this->inhebited = false;
	this->message = "Mjesalica se prazni, a nije izdata komanda za praznjenje! \n";
}

RTU * Alarm::GetRTU()
{
	return rtuDevice;
}

DigitalDevice * Alarm::GetDigitalDevice()
{
	return digitalDevice;
}

string Alarm::GetMessage()
{
	return message;
}

bool Alarm::IsInhibition()
{
	return inhebited;
}

bool Alarm::IsAccepted()
{
	return accepted;
}

void Alarm::SetInhibition(bool value)
{
	inhebited = value;
}

void Alarm::SetAcception(bool value)
{
	accepted = value;
}
