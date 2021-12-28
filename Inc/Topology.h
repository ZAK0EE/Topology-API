#ifndef TOPOLOGY_H_INCLUDED
#define TOPOLOGY_H_INCLUDED
#include <iostream>
#include <map>

class electronic
{
private:
    std::string type, id, valname;
    struct valstruct { float xdefault, min, max; }; valstruct value;
    std::map<std::string, std::string> netlist;
public:
    //setters
    void set_type(const std::string& str);
    void set_id(const std::string& str);
    void set_valname(const std::string& str);
    void set_val_default(float val);
    void set_val_min(float val);
    void set_val_max(float val);
    void netlist_insert(const std::string& key, const std::string& str);
    void netlist_setval(const std::string& key, const std::string& val);
    //getters
    std::string get_type(void);
    std::string get_id(void);
    std::string get_valname(void);
    float get_val_default(void);
    float get_val_min(void);
    float get_val_max(void);
    std::string netlist_getval(const std::string&);
    const std::map<std::string, std::string>* netlist_getall(void);
};

class resistor : public electronic
{
public:
    explicit resistor(const std::string& id);
};

class nmos : public electronic
{
public:
    explicit nmos(const std::string& id);
};

#endif // TOPOLOGY_H_INCLUDED
