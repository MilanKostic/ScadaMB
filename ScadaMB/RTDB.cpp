#include "RTDB.h"

RTDB * RTDB::instance = NULL;

RTDB * RTDB::Instance()
{
	if (instance == NULL) {
		instance = new RTDB();
	}
	return instance;
}

char* RTDB::GetCurrentValues()
{
	string answer;
	answer += "Start";
	
	for each (RTU rtu in listOfRemotes)
	{
		answer += "RTU " + to_string(rtu.GetID());
		for each (AnalogOutput analogOut in rtu.GetAnalogOutoputList())
		{
			answer += "\t" + analogOut.GetName() + " " + to_string(analogOut.GetEgu()) + "\n";
		}
		for each (DigitalDevice dev in rtu.GetDigitalDevices())
		{
			answer += "\t" + dev.GetName() + " " + to_string(dev.GetPointState()) + "\n";
		}
	}
	char * writable = new char[answer.size() + 1];
	copy(answer.begin(), answer.end(), writable);
	writable[answer.size()] = '\0';
	return writable;
}
