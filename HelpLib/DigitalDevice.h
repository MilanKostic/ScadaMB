#pragma once
#include <iostream>
#include <string>
//#include "RTU.h"

#include "PointStates.h"
using namespace std;

class DigitalDevice {
private:
	unsigned short id;
	string name;
	bool isReadOnly;
	unsigned short inAddresses[2];
	unsigned short outAddress;
	PointState state;
	PointStatus status;
	//RTU* rtu;

	PointState command;

public:
	DigitalDevice(unsigned short id, string name, bool readOnly, unsigned short inAddr1, unsigned short inAddr2, unsigned short outAddress, PointState state, PointStatus status, PointState command/*, RTU* rtu*/);
	DigitalDevice(unsigned short id, string name, bool readOnly, unsigned short inAddr1, unsigned short inAddr2, unsigned short outAddress);

	void SetCommand(PointState value);
	void SetState(PointState value);
	void SetStatus(PointStatus value);

	string GetName();
	bool IsReadOnly();
	unsigned short* GetInAddresses();
	unsigned short GetOutAddress();
	unsigned short GetId();
	PointState GetPointState();
	PointStatus GetPointStatus();
//	RTU *GetRTU();
	PointState GetCommand();
};
