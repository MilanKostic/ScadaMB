#pragma once
#include <iostream>
#include <string>
#include "AnalogInput.h"

using namespace std;

class AnalogOutput : public AnalogInput {
private:
	double eguSetpoint;
	int setPointTimestamp;
public:
	AnalogOutput(string name, unsigned short address, double eguMin, 
		double eguMax, double egu, double rawMin, double rawMax, double raw, 
		int timestamp, PointStatus status/*, RTU *rtuDevice*/, double eguSetpoint, int setPointTimestamp);
	AnalogOutput(string name, unsigned short address, double eguMin, double eguMax, double rawMin, double rawMax, int timestamp, double eguSetpoint, int setPointTimestamp);

	void SetEguSetpoint(double value);
	void SetSetPointTimestamp(int value);

	double GetEguSetPoint();
	int GetSetPointTimestamp();
};