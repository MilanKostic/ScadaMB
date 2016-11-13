#include "AnalogOutput.h"

AnalogOutput::AnalogOutput(string name, unsigned short address, double eguMin,
	double eguMax, double egu, double rawMin, double rawMax, double raw, int timestamp,
	PointStatus status/*, RTU *rtuDevice*/, double eguSetpoint, int setPointTimestamp):
	AnalogInput( name,  address,  eguMin,  eguMax,  egu,  rawMin,  rawMax,  raw,  timestamp,  status/*,  rtuDevice*/)
{
	AnalogOutput::eguSetpoint = eguSetpoint;
	AnalogOutput::setPointTimestamp = setPointTimestamp;
}

AnalogOutput::AnalogOutput(string name, unsigned short address, double eguMin, double eguMax, double rawMin, double rawMax, int timestamp, double eguSetpoint, int setPointTimestamp)
	: AnalogInput(name, address, eguMin, eguMax, rawMin, rawMax, timestamp)
{
	this->eguSetpoint = eguSetpoint;
	this->setPointTimestamp = setPointTimestamp;
}

void AnalogOutput::SetEguSetpoint(double value)
{
	eguSetpoint = value;
}

void AnalogOutput::SetSetPointTimestamp(int value)
{
	setPointTimestamp = value;
}

double AnalogOutput::GetEguSetPoint()
{
	return eguSetpoint;
}

int AnalogOutput::GetSetPointTimestamp()
{
	return setPointTimestamp;
}
