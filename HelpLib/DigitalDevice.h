#pragma once
#include <iostream>
#include <string>
#include "RTU.h"

enum PointState {
	Off = 0,
	On,
	Progress,
	Error
};

using namespace std;

class DigitalDevice {
private:
	string name;
	bool isReadOnly;
	unsigned int inAddress[2];
	unsigned int outAddress[2];
	PointState state;
	PointStatus status;
	RTU* rtu;

	PointState command;

public:
	DigitalDevice(string name, bool readOnly, unsigned int inAddress[2], unsigned int outAddress[2], PointState state, PointStatus status, PointState command, RTU* rtu);
	
	void SetCommand(PointState value);
	void SetState(PointState value);
	void SetStatus(PointStatus value);

	string GetName();
	bool IsReadOnly();
	unsigned int GetInAddress();
	unsigned int GetOutAddress();
	PointState GetPointState();
	PointStatus GetPointStatus();
	RTU *GetRTU();
	PointState GetCommand();
};
