#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <vector>
#include "Topology.h"

typedef std::vector<std::shared_ptr<electronic>> DeviceList;
typedef struct topology_s topology_s;
typedef std::vector<std::shared_ptr<topology_s>> TopologyList;

/************************Function prototypes************************/


/*
* readJSON
* @brief      This function reads topology from "FileName" and stored it in the "list"
* 
* @note       FileName is assumed to be a JSON file
* 
* @param[in]  list TopologyList created by the user
* @param[in]  FileName the name of the json file to read from
* @return     returns 1 if success and 0 if there's a problem:
*			  -File could not be opened.
* 
*/
int readJSON(TopologyList& list, const std::string& FileName);


/*
* queryTopologies
* @brief      This function return a list of strings of topologies IDs
*
* @param[in]  list TopologyList created by the user
* @return     returns a vector of strings to topologies IDs.
*			  -File could not be opened.
*
*/
std::vector<std::string> queryTopologies(TopologyList& list);


 /*
 * writeJSON
 * @brief      This function writes the given "topology" into the "FileName" in JSON structured-style
 *
 * @note       FileName is assumed to be a JSON file
 *
 * @param[in]  topology is a topology given by the user
 * @param[in]  FileName the name of the json file to write to
 * @return     Returns 1 if success and 0 if there's a problem:
 *		       -File could not be opened.
 *			   -The topology id is NULL
 */
int writeJSON(std::shared_ptr<topology_s> topology, const std::string& FileName);


/*
* deleteTopology
* @brief      This function deletes a Topology from the given "list" identified by the "TopologyID"
*
*
* @param[in]  list TopologyList created by the user
* @param[in]  TopologyID The ID of the topology wanted to be deleted
* @return     Returns 1 if topology is found and deleted, and 0 if there's a problem:
*		       -Topology could not be found
*/
int deleteTopology(TopologyList& list, const std::string& TopologyID);


/*
* queryDevices
* @brief  This function iterates over the TopologyList and returns a DeviceList for a Topology with id "TopologyID"
*
*
* @param[in]  list TopologyList created by the user
* @param[in]  TopologyID The ID of the topology wanted to be returned
* @return     Returns a DeviceList for the Topology with ID "TopologyID"
*		      -returns empty DeviceList if "TopologyID" not found
*/
DeviceList queryDevices(TopologyList& list, const std::string& TopologyID);


/*
* queryDevicesWithNetlistNode
* @brief  This function iterates over the Topology's components with ID "TopologyID" and returns a DeviceList 
* that contains all components that are connected to the netlist node.
*
*
* @param[in]  list TopologyList created by the user
* @param[in]  TopologyID The ID of the topology wanted to be checked
* @return     Returns a DeviceList for components that are connected to the "NetlistNodeID"
*		      -returns empty DeviceList if "TopologyID" not found
*/
DeviceList queryDevicesWithNetlistNode(TopologyList& list, const std::string& TopologyID, const std::string& NetlistNodeID);

#endif // API_H_INCLUDED
