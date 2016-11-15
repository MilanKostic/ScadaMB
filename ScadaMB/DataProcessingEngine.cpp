#include "DataProcessingEngine.h"

DataProcessingEngine::DataProcessingEngine() {}

void DataProcessingEngine::AddHostPoll(int rtuId, HostPoll* hostPoll)
{
	lock.lock();
	if (this->remotes.find(rtuId) == this->remotes.end())
	{
		this->remotes.insert(std::pair<int, list<HostPoll*>*>(rtuId, new list<HostPoll*>()));
	}
	list<HostPoll*>* rtu = this->remotes[rtuId];
	rtu->push_back(hostPoll);
	lock.unlock();
}

void DataProcessingEngine::Process()
{
	while (true)
	{
		for each(std::pair<int, list<HostPoll*>*> rtu in this->remotes)
		{
			lock.lock();
			while (rtu.second->size() != 0) // Mozda treba promijeniti ???
			{
				HostPoll* first = rtu.second->front();
				rtu.second->pop_front();
				first->GetResponse()->Crunch(rtu.first, first->GetRequest());
				delete first;
			}
			lock.unlock();
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

