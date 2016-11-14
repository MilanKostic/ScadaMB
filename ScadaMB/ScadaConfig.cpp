#include "ScadaConfig.h"


ScadaConfig::ScadaConfig()
{
}

void ScadaConfig::LoadScadaParams()
{
	string inputXml;
	string line;
	ifstream in(configFile);

	while (getline(in, line))
	{
		inputXml += line + "\n";
	}
	vector<char> xml_copy(inputXml.begin(), inputXml.end());
	xml_copy.push_back('\0');

	xml_document<> doc;
	doc.parse<0>(&xml_copy[0]);

	xml_node<> *current = doc.first_node()->first_node();

	while(current)
	{
		xml_attribute<>* attr = current->first_attribute("id");
		this->InsertRTU(current, atoi(attr->value()));
		current = current->next_sibling();
	}
	
}

void ScadaConfig::InsertRTU(const xml_node<>* current, int rtuId)
{
	
	const node_type t = current->type();
	switch (t) {
		case node_element:
		{
			if (current->name() == ScadaConfig::rtuNode)
			{
				int id = atoi(current->first_attribute("id")->value());
				string industrialProtocol = current->first_attribute("industrialProtocol")->value();
				string transportProtocol = current->first_attribute("transportProtocol")->value();
				string ipAddress = current->first_attribute("ipAddress")->value();
				int port = atoi(current->first_attribute("port")->value());

				RTU* newRTU = new RTU(id, industrialProtocol, transportProtocol, ipAddress, port);
				RTDB::Instance()->AddRTU(newRTU);
			}
			else if (current->name() == ScadaConfig::analogInputNode)
			{
				string name = current->first_attribute("name")->value();
				unsigned short address = (unsigned short)atoi(current->first_attribute("address")->value());
				double eguMin = stod(current->first_attribute("eguMin")->value());
				double eguMax = stod(current->first_attribute("eguMax")->value());
				double rawMin = stod(current->first_attribute("rawMin")->value());
				double rawMax = stod(current->first_attribute("rawMax")->value());
				int timeStamp = atoi(current->first_attribute("timeStamp")->value());

				AnalogInput* newAnalogInput = new AnalogInput(name, address, eguMin, eguMax, rawMin, rawMax, timeStamp);
				RTDB::Instance()->GetRTU(rtuId)->AddAnalogInput(newAnalogInput);
			}
			else if (current->name() == ScadaConfig::analogOutputNode)
			{
				string name = current->first_attribute("name")->value();
				unsigned short address = (unsigned short)atoi(current->first_attribute("address")->value());
				double eguMin = stod(current->first_attribute("eguMin")->value());
				double eguMax = stod(current->first_attribute("eguMax")->value());
				double rawMin = stod(current->first_attribute("rawMin")->value());
				double rawMax = stod(current->first_attribute("rawMax")->value());
				int timeStamp = atoi(current->first_attribute("timeStamp")->value());

				AnalogOutput* newAnalogOutput = new AnalogOutput(name, address, eguMin, eguMax, rawMin, rawMax, timeStamp, 0.00, 0);
				RTDB::Instance()->GetRTU(rtuId)->AddAnalogOutput(newAnalogOutput);
			}
			else if (current->name() == ScadaConfig::digitalDevice)
			{
				unsigned short id = (unsigned short)atoi(current->first_attribute("id")->value());
				string name = current->first_attribute("name")->value();
				bool isReadOnly = current->first_attribute("isReadOnly")->value() == "true";
				unsigned short addr1 = (unsigned short)atoi(current->first_attribute("inAddress1")->value());
				unsigned short addr2 = (unsigned short)atoi(current->first_attribute("inAddress2")->value());
				unsigned short outAddress = (unsigned short)atoi(current->first_attribute("outAddress")->value());

				DigitalDevice* newDigitalDevice = new DigitalDevice(id, name, isReadOnly, addr1, addr2, outAddress);
				RTDB::Instance()->GetRTU(rtuId)->AddDigitalDevice(newDigitalDevice);
			}
			
			for (xml_node<>* n = current->first_node(); n; n = n->next_sibling())
			{
				this->InsertRTU(n, rtuId);
			}
		}
		default:
			break;
	}
	
}
