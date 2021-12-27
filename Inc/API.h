#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include "json.hpp"
#include "Topology.h"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

typedef std::vector<std::shared_ptr<electronic>> Devicelist;

typedef struct 
{
	std::string id;
	Devicelist devices;

}topology_s;

typedef std::vector<topology_s> TopologyList;

topology_s readJSON(std::string FileName);
void writeJSON(topology_s toplogy, std::string FileName);

#endif // API_H_INCLUDED
