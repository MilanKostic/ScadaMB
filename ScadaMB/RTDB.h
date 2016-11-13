#pragma once
#include "PointAddress.h"
#include <iostream>
#include "RTU.h"
#include <list>

class RTDB {
private:
	static RTDB *instance;
	map<int, RTU*> listOfRemotes;
public:
	static RTDB *Instance();
	char *GetCurrentValues();
	map<int, RTU*> GetRemotes();
	map<int, RTU*> AddRTU(RTU *device);
	RTU* GetRTU(int id);
};