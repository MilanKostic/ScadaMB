#include "DataProcessingEngine.h"

DataProcessingEngine::DataProcessingEngine() {}

void DataProcessingEngine::AddHostPoll(int rtuId, HostPoll* hostPoll)
{
	if (this->remotes.find(rtuId) == this->remotes.end())
	{
		this->remotes.insert(std::pair<int, list<HostPoll*>>(rtuId, list<HostPoll*>()));
	}
	list<HostPoll*> rtu = this->remotes[rtuId];
	rtu.push_back(hostPoll);
}

void DataProcessingEngine::Process()
{
	// Azuriranje vrijednosti u rtdb
}

