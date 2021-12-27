#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Topology.h"
#include "json.hpp"

#include "API.h"




topology_s readJSON(std::string FileName)
{
	json topjson;

	std::ifstream jsonfile(FileName);

	//Streaming jsonfile into the topjson -memory-
	jsonfile >> topjson;




	//Topology
	topology_s topology;

	topology.id = topjson["id"].get<std::string>();

	int compsize = topjson["components"].size();


	for (int i = 0; i < compsize; i++)
	{
		std::string type = topjson["components"][i]["type"];
		std::unique_ptr<electronic> device;

		//Choosing the suitable class.
		if (type == "resistor")
			device = std::make_unique<resistor>(topjson["components"][i]["id"]);
		else if (type == "nmos")
			device = std::make_unique<nmos>(topjson["components"][i]["id"]);

		else
		{
			//Can be replaced with any error handler
			//std::cout << "[ERROR]Unrecognized device id: " << topjson["components"][i]["id"] << '\n';
			continue;
		}

		float tempval;
		//Retrieving default value
		tempval = topjson["components"][i][device->get_valname()]["default"].get<float>();
		device->set_val_default(tempval);

		//Retrieving min value
		tempval = topjson["components"][i][device->get_valname()]["min"].get<float>();
		device->set_val_min(tempval);

		//Retrieving max value
		tempval = topjson["components"][i][device->get_valname()]["max"].get<float>();
		device->set_val_max(tempval);

		//Retrieving netlist values
		for (const auto& item : topjson["components"][i]["netlist"].items())
			device->netlist_setval(item.key(), item.value());

		topology.devices.push_back(std::move(device));
	}
	return topology;
}


void writeJSON(topology_s topology, std::string FileName)
{
	ordered_json j;
	j["id"] = topology.id;
	Devicelist list = topology.devices;
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

	std::ofstream out("out.json");
	out << std::setprecision(2) << std::setw(2) << j;
}