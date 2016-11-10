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
	answer += "Current values: \n";
	for each (RTU rtu in listOfRemotes)
	{
		answer += "RTU " + to_string(rtu.GetID());
		for each (pair<unsigned int,AnalogOutput> analogOut in rtu.GetAnalogOutoputList())
		{
			answer += "\t" + analogOut.second.GetName() + " " + to_string(analogOut.second.GetEgu()) + "\n";
		}
		for each (pair<unsigned int, AnalogInput> analogIn in rtu.GetAnalogOutoputList())
		{
			answer += "\t" + analogIn.second.GetName() + " " + to_string(analogIn.second.GetEgu()) + "\n";
		}
		for each (pair<unsigned int, DigitalDevice> dev in rtu.GetDigitalDevices())
		{
			answer += "\t" + dev.second.GetName() + " " + to_string(dev.second.GetPointState()) + "\n";
		}
	}
	char * writable = new char[answer.size() + 1];
	copy(answer.begin(), answer.end(), writable);
	writable[answer.size()] = '\0';
	return writable;
}
