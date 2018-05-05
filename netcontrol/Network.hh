#pragma once

#include <vector>
#include "component.hh"
#include "Topology.hh"
#include "Vlset.hh"
#include "Vl.hh"

using namespace vigil;
using namespace vigil::container;


class Network {
public:
	Network(const VLSet &vls, const Topology &map, Component *c);

	VLSet vlTable() const;
	Topology map() const;

	void addVL(const VL &vl);
	void addVLs(const std::vector<VL> &vls);
	void removeVL(const VL &vl);
	void removeVLs(const std::vector<VL> &vls);
	void changeVL(const VL &vl, const VL &vl_new);
	void changeVLs(const std::vector<VL> &vls, const std::vector<VL> &vls_new);

	void breakComm();
	void breakLink();
	void breakHost(uint32_t id);
private:
	VLSet vls;
	Topology topo;
	Component *app;

	void setRules(std::vector<Settings> settings);
};
