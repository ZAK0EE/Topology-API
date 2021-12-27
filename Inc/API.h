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



typedef std::string Result;
//Function prototypes

Result readJSON(TopologyList* TopologyList_t, std::string FileName);
Result writeJSON(std::shared_ptr<topology_s>, std::string FileName);
Result deleteTopology(TopologyList& TopologyList_t, std::string TopologyID);

#endif // API_H_INCLUDED
