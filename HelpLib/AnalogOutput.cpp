#include "AnalogOutput.h"

AnalogOutput::AnalogOutput(string name, unsigned short address, double eguMin,
	double eguMax, double egu, double rawMin, double rawMax, double raw, int timestamp,
	PointStatus status/*, RTU *rtuDevice*/, double eguSetpoint, int setPointTimestamp):
	AnalogInput( name,  address,  eguMin,  eguMax,  egu,  rawMin,  rawMax,  raw,  timestamp,  status/*,  rtuDevice*/)
{
	AnalogOutput::eguSetpoint = eguSetpoint;
	AnalogOutput::setPointTimestamp = setPointTimestamp;
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
