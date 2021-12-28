# Topology API
## Features
#### Provide the functionality to:
- Read a topology from a given JSON file and store it in the memory.
- Write a given topology from the memory to a JSON file.
- Query about which topologies are currently in the memory.
- Delete a given topology from memory.
- Query about which devices are in a given topology.
- Query about which devices are connected to a given netlist node in a given topology.

    TopologyList
    topologie
## API functions
```c++
int readJSON(TopologyList& list, const std::string& FileName);
std::vector<std::string> queryTopologies(TopologyList& list);
int writeJSON(std::shared_ptr<topology_s> topology, const std::string& FileName);![datastructureDiagram](https://user-images.githubusercontent.com/82421473/147602045-2ee00f9a-b20d-47d4-86bb-f8edc54837cd.png)
![datastructureDiagram](https://user-images.githubusercontent.com/82421473/147602125-8f7ee6df-5411-4677-ba10-99e6a5b2a7d3.png)

int deleteTopology(TopologyList& list, const std::string& TopologyID);
DeviceList queryDevices(TopologyList& list, const std::string& TopologyID);![datastructureDiagram](https://user-images.githubusercontent.com/82421473/147601864-5def9fea-5702-43b3-bcb5-84733fa0c3f5.png)

DeviceList queryDevicesWithNetlistNode(TopologyList& list, const std::string& TopologyID, const std::string& NetlistNodeID);
```

![Data structure diagram](diagrams/datastructureDiagram.png)



