#pragma once
#include <iostream>
#include <string>
//#include "RTU.h"

#include "PointStates.h"
using namespace std;

class DigitalDevice {
private:
	string name;
	bool isReadOnly;
	unsigned short inAddress[2];
	unsigned short outAddress[2];
	PointState state;
	PointStatus status;
	//RTU* rtu;

	PointState command;

public:
	DigitalDevice(string name, bool readOnly, unsigned int inAddress[2], unsigned int outAddress[2], PointState state, PointStatus status, PointState command/*, RTU* rtu*/);
	
	void SetCommand(PointState value);
	void SetState(PointState value);
	void SetStatus(PointStatus value);

	string GetName();
	bool IsReadOnly();
	unsigned short GetInAddress();
	unsigned short GetOutAddress();
	PointState GetPointState();
	PointStatus GetPointStatus();
//	RTU *GetRTU();
	PointState GetCommand();
};
