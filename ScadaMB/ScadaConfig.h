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
	const string digitalDevice = "digitalDevice";
	void InsertRTU(const xml_node<>* node, int rtuId);
public:
	ScadaConfig();
	void LoadScadaParams();
};