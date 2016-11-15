#include "AnalogInput.h"


AnalogInput::AnalogInput(string name, unsigned short address, double eguMin, double eguMax, double egu, double rawMin, double rawMax, double raw, int timestamp, PointStatus status/*, RTU *rtuDevice*/)
{
	AnalogInput::name = name;
	AnalogInput::address = address;
	AnalogInput::eguMin = eguMin;
	AnalogInput::eguMax = eguMax;
	AnalogInput::egu = egu;
	AnalogInput::rawMin = rawMin;
	AnalogInput::rawMax = rawMax;
	AnalogInput::raw = raw;
	AnalogInput::timeStamp = timestamp;
	AnalogInput::status = status;
	//AnalogInput::rtu = rtu;
}

AnalogInput::AnalogInput(string name, unsigned short address, double eguMin, double eguMax, double rawMin, double rawMax, int timestamp)
{
	AnalogInput::name = name;
	AnalogInput::address = address;
	AnalogInput::eguMin = eguMin;
	AnalogInput::eguMax = eguMax;
	AnalogInput::rawMin = rawMin;
	AnalogInput::rawMax = rawMax;
	AnalogInput::timeStamp = timestamp;
}

string AnalogInput::GetName()
{
	return name;
}

unsigned short AnalogInput::GetAddress()
{
	return address;
}

double AnalogInput::GetEguMin()
{
	return eguMin;
}

double AnalogInput::GetEguMax()
{
	return eguMax;
}

double AnalogInput::GetEgu()
{
	return egu;
}

double AnalogInput::GetRawMin()
{
	return rawMin;
}

double AnalogInput::GetRawMax()
{
	return rawMax;
}

double AnalogInput::GetRaw()
{
	return raw;
}

int AnalogInput::GetTimestamp()
{
	return timeStamp;
}

PointStatus AnalogInput::GetStatus()
{
	return status;
}
/*
RTU *AnalogInput::GetRTU()
{
	return rtu;
}*/

void AnalogInput::SetEguMin(double value)
{
	eguMin = value;
}

void AnalogInput::SetEguMax(double value)
{
	eguMax = value;
}

void AnalogInput::SetEgu(double value)
{
	egu = value;
}

void AnalogInput::SetRawMin(double value)
{
	rawMin = value;
}

void AnalogInput::SetRawMax(double value)
{
	rawMax = value;
}

void AnalogInput::SetRaw(double value)
{
	raw = value;
	egu = ToEgu(raw);
}

void AnalogInput::SetTimestamp(int value)
{
	timeStamp = value;
}

void AnalogInput::SetPointStatus(PointStatus value)
{
	status = value;
}
unsigned short AnalogInput::ToRaw(double egu)
{
	return egu / (10 * 1.00);
}
double AnalogInput::ToEgu(unsigned short raw)
{
	return raw * 10; //
}
/*
void AnalogInput::SetRTU(RTU *value)
{
	rtu = value;
}
*/