#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include "json.hpp"
#include "Topology.h"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

typedef std::vector<std::shared_ptr<electronic>> Devicelist;

typedef struct topology_s
{
	std::string id;
	Devicelist devices;

}topology_s;


typedef std::vector<std::shared_ptr<topology_s>> TopologyList;

//Topology list 

typedef std::string Result;
Result readJSON(std::string FileName);
void writeJSON(std::shared_ptr<topology_s>, std::string FileName);

#endif // API_H_INCLUDED
