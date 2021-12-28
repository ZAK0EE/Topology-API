/*
* This file represents an eaxmple of how to use Topology API
* Topology API was created by: Ziad Gamalelden under request from : Master Micro
* 
*/

#include <iostream>
#include <vector>
#include "API.h"

void Print_Tops_Components(TopologyList &list)
{
	// Getting current Topologies' IDs stored in list
	std::vector<std::string> id_list = queryTopologies(list);

	// Iterating over the list, querying devicelist for each topology
	for (int i = 0, n = list.size(); i < n; i++)
	{
		DeviceList dlist = queryDevices(list, id_list[i]);
		std::cout << id_list[i] << ": {";
		// Iterating over the device list and printing the components IDs.
		for (int j = 0, dn = dlist.size(); j < dn; j++)
		{
			std::cout << dlist[j]->get_id();
			if (j != dn - 1)
				std::cout << ", ";
		}
		std::cout << "}\n";
	}
}
int main()
{
	TopologyList list;
	// Reading two topologies from two files (Every file must have one topology)
	if (!readJSON(list, "input/Topology1.json"))
		std::cout << "File could not be accessed" << '\n';
	if (!readJSON(list, "input/Topology2.json"))
		std::cout << "File could not be accessed" << '\n';

	// Print all components in each topology
	Print_Tops_Components(list);
	
	deleteTopology(list, "top1");

	std::cout << "\nAfter deletion:\n";
	Print_Tops_Components(list);

	DeviceList conencted_devices = queryDevicesWithNetlistNode(list, "top2", "n1");
	std::cout << "\nDevices connected to netlise node \"n1\" in \"top2\" are: ";
	std::cout << "{";
	for (int i = 0, n = conencted_devices.size(); i < n; i++)
	{
		std::cout << conencted_devices[i]->get_id();
		if (i != n - 1)
			std::cout << ", ";
	}
	std::cout << "}\n";

	if (!writeJSON(list[0], "ouput/Output.json"))
	{
		std::cout << "Couldn't write to Output.json" << '\n';
	}
	





}

