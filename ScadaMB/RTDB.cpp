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
		//answer += "RTU " + rtu.GetID() + "\n";
		answer.append("RTU ").append(to_string(rtu.GetID())).append("\n");
		/*for each (AnalogOutput analogOut in rtu.GetAnalogOutoputList())
		{
			answer.append("\t").append(" rtu")
				//.append(analogOut.GetName()).append(" ").append(analogOut.GetEgu()).append("\n");
		}
		for each (DigitalDevice dev in rtu.GetDigitalDevices())
		{
			//answer += "\t" + dev.GetName() + " " + dev.GetPointState() + "\n";
		}*/
	}
	answer += '\0';
	return (char*)answer.c_str();
}
