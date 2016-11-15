#pragma once

#include "ModbusMessageTCP.h"
#include "HostPoll.h"

#include <map>
#include <list>
#include <mutex>

using namespace std;

class DataProcessingEngine
{
private:
	map<int, list<HostPoll*>*> remotes; //key = rtu id, value = HostPoll
	mutex lock;
public:
	DataProcessingEngine();
	void AddHostPoll(int rtuId, HostPoll* hostPoll);
	void Process();
};

