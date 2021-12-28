#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <vector>
#include "Topology.h"

typedef std::vector<std::shared_ptr<electronic>> Devicelist;
typedef struct topology_s topology_s;
typedef std::vector<std::shared_ptr<topology_s>> TopologyList;

typedef std::string Result;

//Function prototypes
int readJSON(TopologyList& list, const std::string& FileName);
int writeJSON(std::shared_ptr<topology_s> topology, const std::string& FileName);
int deleteTopology(TopologyList& list, const std::string& TopologyID);
Devicelist queryDevices(TopologyList& list, const std::string& TopologyID);
Devicelist queryDevicesWithNetlistNode(TopologyList& list, const std::string& TopologyID, const std::string& NetlistNodeID);
//Devicelist queryDevicesTopologyList& (TopologyID);
#endif // API_H_INCLUDED
