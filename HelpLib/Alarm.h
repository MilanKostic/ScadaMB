#pragma once
#include <stdio.h>
#include "RTU.h"

class Alarm{
private:
	int id;
	RTU *rtuDevice;
	DigitalDevice *digitalDevice;
	string message;

	bool inhebited;
	bool accepted;
	int sleepTime;
	bool isSend;
public:
	Alarm(RTU *rtuDevice, DigitalDevice *digitalDevice, int id);
	RTU *GetRTU();
	DigitalDevice *GetDigitalDevice();
	string GetAlarmMessage();
	bool IsInhibition();
	bool IsAccepted();

	void SetInhibition(bool value);
	void SetAcception(bool value);
	int GetSleepTime();
	void setSleepTime(int sl);
	void SetId(int id);
	int GetAlarmId();
	void SetIsSend(bool f);
	bool GetIsSend();
};