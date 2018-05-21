#pragma once

#include <vector>
#include "component.hh"
#include "Topology.hh"
#include "Vl.hh"

using namespace vigil;
using namespace vigil::container;


class Network {
public:
	Network(const VLSet &vls, const Topology &map, Component *c);

	VLSet vlTable() const;
	Topology map() const;

	void addVL(const VL &vl);
	void addVLs(const VLSet &vls);
	void removeVL(const VL &vl);
	void removeVLs(const VLSet &vls);
	void changeVL(const VL &vl);
	void changeVLs(const VLSet &vls_new);

	void breakComm(uint32_t s1);
	void breakLink(uint32_t s1, uint32_t s2);
	void breakHost(uint32_t id);
	void updateTopo(Topology topo);
	void configure();
private:
	VLSet vls;
	Topology topo;
	Component *app;

	void setRules(std::vector<Settings> settings);
};
