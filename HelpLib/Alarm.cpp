#include "Alarm.h"

Alarm::Alarm(RTU * rtuDev, DigitalDevice * digitalDev, int id)
{
	rtuDevice = rtuDev;
	digitalDevice = digitalDev;
	this->accepted = false;
	this->inhebited = false;
	this->message = "Mjesalica se prazni, a nije izdata komanda za praznjenje! \n";
	this->id = id;
	this->sleepTime = 0;
	this->isSend = false;
}

RTU * Alarm::GetRTU()
{
	return rtuDevice;
}

DigitalDevice * Alarm::GetDigitalDevice()
{
	return digitalDevice;
}

string Alarm::GetAlarmMessage()
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
	sleepTime = 5000;
	accepted = value;
}

int Alarm::GetSleepTime()
{
	return this->sleepTime;
}

void Alarm::setSleepTime(int sl)
{
	this->sleepTime = sl;
}

void Alarm::SetId(int id)
{
	this->id = id;
}

int Alarm::GetAlarmId()
{
	return id;
}

void Alarm::SetIsSend(bool s)
{
	this->isSend = s;
}

bool Alarm::GetIsSend()
{
	return this->isSend;
}
