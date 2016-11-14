#pragma once

#include "RTDB.h"
#include <thread>
#include <chrono>
#include "DataProcessingEngine.h"

class PollEngine
{
private:
	const unsigned short sendInterval = 2000;
	DataProcessingEngine dataProcessingEngine;
public:
	PollEngine();
	void Poll();
	DataProcessingEngine* GetDPE();
};

void PollThread(PollEngine* pollEngine);
void ProcessThread(DataProcessingEngine* dpe);