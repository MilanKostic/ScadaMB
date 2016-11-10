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
	for each (pair<int, RTU*> rtu in listOfRemotes)
	{
		answer += "RTU " + to_string(rtu.second->GetID());
		for each (pair<unsigned int,AnalogOutput> analogOut in rtu.second->GetAnalogOutoputList())
		{
			answer += "\t" + analogOut.second.GetName() + " " + to_string(analogOut.second.GetEgu()) + "\n";
		}
		for each (pair<unsigned int, AnalogInput> analogIn in rtu.second->GetAnalogOutoputList())
		{
			answer += "\t" + analogIn.second.GetName() + " " + to_string(analogIn.second.GetEgu()) + "\n";
		}
		for each (pair<unsigned int, DigitalDevice> dev in rtu.second->GetDigitalDevices())
		{
			answer += "\t" + dev.second.GetName() + " " + to_string(dev.second.GetPointState()) + "\n";
		}
	}
	char * writable = new char[answer.size() + 1];
	copy(answer.begin(), answer.end(), writable);
	writable[answer.size()] = '\0';
	return writable;
}

map<int, RTU*> RTDB::GetRemotes()
{
	return listOfRemotes;
}

map<int, RTU*> RTDB::AddRTU(RTU * device)
{
	listOfRemotes.insert(std::pair<int, RTU*>(device->GetID(), device));
	return listOfRemotes;
}
