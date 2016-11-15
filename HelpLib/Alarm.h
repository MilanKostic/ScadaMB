#pragma once
#include <stdio.h>
#include "RTU.h"

class Alarm{
private:
	RTU *rtuDevice;
	DigitalDevice *digitalDevice;
	string message;

	bool inhebited;
	bool accepted;
public:
	Alarm(RTU *rtuDevice, DigitalDevice *digitalDevice);
	RTU *GetRTU();
	DigitalDevice *GetDigitalDevice();
	string GetMessage();
	bool IsInhibition();
	bool IsAccepted();

	void SetInhibition(bool value);
	void SetAcception(bool value);
};