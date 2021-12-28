#include "Topology.h"

//*******************resistor class functions definition*******************//
//setters
void electronic::set_type(const std::string &str)
{
    type = str;
}
void electronic::set_id(const std::string& str)
{
    id = str;
}
void electronic::set_valname(const std::string& str)
{
    valname = str;
}
void electronic::set_val_default(float val)
{
    value.xdefault = val;
}
void electronic::set_val_min(float val)
{
    value.min = val;
}
void electronic::set_val_max(float val)
{
    value.max = val;
}
void electronic::netlist_insert(const std::string& key, const std::string& str)
{
    netlist.insert({ key, str});
}
void electronic::netlist_setval(const std::string& key, const std::string& val)
{
    netlist[key] = val;
}
//getters
std::string electronic::get_type(void)
{
    return type;
}
std::string electronic::get_id(void)
{
    return id;
}
std::string electronic::get_valname(void)
{
    return valname;
}
float electronic::get_val_default(void)
{
    return value.xdefault;
}
float electronic::get_val_min(void)
{
    return value.min;
}
float electronic::get_val_max(void)
{
    return value.max;
}
std::string electronic::netlist_getval(const std::string& key)
{
    return netlist[key];
}
const std::map<std::string, std::string>* electronic::netlist_getall(void)
{
    return &netlist;
}

//*******************resistor class functions definition*******************//
resistor::resistor(const std::string& id = "NULL")
{
    set_type("resistor");
    set_id(id);
    set_valname("resistance");
    netlist_insert("t1", "NULL");
    netlist_insert("t2", "NULL");
}
//*******************nmos class functions definition*******************//
nmos::nmos(const std::string& id = "NULL")
{
    set_type("nmos");
    set_id(id);
    set_valname("m(l)");
    netlist_insert("drain", "NULL");
    netlist_insert("gate", "NULL");
    netlist_insert("source", "NULL");
}