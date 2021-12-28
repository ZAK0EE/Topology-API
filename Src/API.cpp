#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Topology.h"
#include "json.hpp"

#include "API.h"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;


 struct topology_s
{
	std::string id;
	DeviceList devices;

};

 
 int readJSON(TopologyList& list, const std::string& FileName)
 {
	 json topjson;
	std::ifstream jsonfile(FileName);

	// Error handler.
	if (!jsonfile.is_open())
	{
		return 0;
	}

	// Streaming jsonfile into the topjson -memory-
	jsonfile >> topjson;


	// Topology
	std::unique_ptr<topology_s> topology = std::make_unique<topology_s>();

	topology->id = topjson["id"].get<std::string>();
	
	int compsize = topjson["components"].size();
	// Iterating over the components
	for (int i = 0; i < compsize; i++)
	{
		std::string type = topjson["components"][i]["type"];
		std::unique_ptr<electronic> device;

		// Choosing the suitable class
		if (type == "resistor")
			device = std::make_unique<resistor>(topjson["components"][i]["id"]);
		else if (type == "nmos")
			device = std::make_unique<nmos>(topjson["components"][i]["id"]);
		else
		{
			//Can be replaced with any error handler
			//std::cout << "[ERROR]Unrecognized type for device: " << topjson["components"][i]["id"] << '\n';
			continue;
		}

		float tempval;
		// Retrieving default value
		tempval = topjson["components"][i][device->get_valname()]["default"].get<float>();
		device->set_val_default(tempval);

		// Retrieving min value
		tempval = topjson["components"][i][device->get_valname()]["min"].get<float>();
		device->set_val_min(tempval);

		// Retrieving max value
		tempval = topjson["components"][i][device->get_valname()]["max"].get<float>();
		device->set_val_max(tempval);

		// Retrieving netlist values
		for (const auto& item : topjson["components"][i]["netlist"].items())
			device->netlist_setval(item.key(), item.value());
		
		topology->devices.push_back(std::move(device));
	}
	list.push_back(move(topology)); //topology list.

	return 1;
	
}

std::vector<std::string> queryTopologies(TopologyList& list)
{
	std::vector<std::string> topid_list;
	for (int i = 0, n = list.size(); i < n; i++)
	{
		topid_list.push_back(list[i]->id);
	}
	return topid_list;
}

int writeJSON(std::shared_ptr<topology_s> topology, const std::string& FileName)
{
	if(topology->id.compare("NULL") == 0)
		return 0;

	ordered_json j; //using "ordered json" instead of "json" only is to maintain the order as inputted.
	j["id"] = topology->id;
	DeviceList list = topology->devices;
	
	int compsize = list.size();

	for (int i = 0; i < compsize; i++)
	{
		
		j["components"][i] =
		{
				{"type", list[i]->get_type()},
				{"id", list[i]->get_id()},
				{list[i]->get_valname(),
					{
						{"default", list[i]->get_val_default()},
						{"min", list[i]->get_val_min()},
						{"max", list[i]->get_val_max()}
					}
				}
		};
		const std::map<std::string, std::string>* netlist = list[i]->netlist_getall();
		for (auto const& [k, v] : *netlist)
			j["components"][i]["netlist"][k] = v;
	}

	std::ofstream outfile(FileName);
	// Error handler
	if (!outfile.is_open())
	{
		return 0;
	}
	// Straeming the json structure into the file
	outfile << std::setw(2) << j;
	return 1;
}



int deleteTopology(TopologyList& list, const std::string& TopologyID)
{ 
	bool found = false;
	for (int i = 0, n = list.size(); i < n; i++) 
	{
		if (list[i]->id.compare(TopologyID) == 0)
		{
			list.erase(list.begin() + i);
			found = true;
			break;
		}

	}
	return found;
}

DeviceList queryDevices(TopologyList& list, const std::string& TopologyID)
{
	DeviceList devlist;
	for (int i = 0, n = list.size(); i < n; i++) 
	{
		if (list[i]->id.compare(TopologyID) == 0)
		{
			devlist = list[i]->devices;
			break;
		}

	}
	// Will return empty list in case no devices found
	return devlist;
}

DeviceList queryDevicesWithNetlistNode(TopologyList& list, const std::string& TopologyID, const std::string& NetlistNodeID)
{
	DeviceList devlist = queryDevices(list, TopologyID);
	DeviceList connected; // Device list for devices connected to the netlist node.
	for (int i = 0, n = devlist.size(); i < n; i++)
	{
		const std::map<std::string, std::string>* netlist = devlist[i]->netlist_getall();
		for (auto const& [k, v] : *netlist)
		{
			//v is the netlist node ID and k is the key.
			if (NetlistNodeID.compare(v) == 0)
			{
				connected.push_back(devlist[i]);
				break;
			}
		}
	}


	return connected;
}