#pragma once

#include "RTDB.h"
#include <string>
#include "rapidxml_utils.hpp"
#include <vector>

using namespace std;
using namespace rapidxml;

class ScadaConfig
{
private:
	const string configFile = "config.xml";
	const string rootNode = "scada_config";
	const string rtuNode = "rtu";
	const string analogInputNode = "analogInput";
	const string analogOutputNode = "analogOutput";
	const string digitalInputNode = "digitalInput";
	const string digitalOutputNode = "digitalOutput";
	void InsertRTU(const xml_node<>* node, RTDB* realTimeDatabase, int rtuId);
public:
	ScadaConfig();
	void LoadScadaParams(RTDB* realTimeDatabase);
};