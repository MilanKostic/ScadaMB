#pragma once
#include <iostream>
#include <string>
#include "AnalogInput.h"

using namespace std;

class AnalogOutput : AnalogInput {
private:
	double eguSetpoint;
	int setPointTimestamp;
public:
	AnalogOutput(string name, string address, double eguMin, 
		double eguMax, double egu, double rawMin, double rawMax, double raw, 
		int timestamp, PointStatus status, RTU *rtuDevice, double eguSetpoint, int setPointTimestamp);

	void SetEguSetpoint(double value);
	void SetSetPointTimestamp(double value);

	double GetEguSetPoint();
	int GetSetPointTimestamp();
};