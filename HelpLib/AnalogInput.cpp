#include "AnalogInput.h"


AnalogInput::AnalogInput(string name, string address, double eguMin, double eguMax, double egu, double rawMin, double rawMax, double raw, int timestamp, PointStatus status/*, RTU *rtuDevice*/)
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

string AnalogInput::GetName()
{
	return name;
}

string AnalogInput::GetAddress()
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
}

void AnalogInput::SetTimestamp(int value)
{
	timeStamp = value;
}

void AnalogInput::SetPointStatus(PointStatus value)
{
	status = value;
}
/*
void AnalogInput::SetRTU(RTU *value)
{
	rtu = value;
}
*/