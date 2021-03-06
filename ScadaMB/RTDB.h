#pragma once
#include "PointAddress.h"
#include <iostream>
#include "RTU.h"
#include <list>
#include "Alarm.h"

class RTDB {
private:
	static RTDB *instance;
	map<int, RTU*> listOfRemotes;
	map<int, list<Alarm*>*> alarmList; // key je id RTU-a, value je lista alarma na njemu
	int alarmCount;
	mutex alarmMutex;
	RTDB();
public:
	~RTDB();
	static RTDB *Instance();
	char *GetCurrentValues();
	map<int, RTU*> GetRemotes();
	map<int, RTU*> AddRTU(RTU *device);
	RTU* GetRTU(int id);

	map<int, list<Alarm*>*> GetAlarmMap();
	void AddAlarm(Alarm *newAlarm);
	void ProcessAlarm(int alarmId, char c);
	void RemoveAlarm(DigitalDevice* device);
};