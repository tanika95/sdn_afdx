#pragma once

#include <vector>
#include "component.hh"
#include "Host.hh"
#include "Vlset.hh"
#include "Vl.hh"

using namespace vigil;
using namespace vigil::container;


class Network {
public:
	Network(const VLSet &vls, const std::vector<Host> &hsts, Component *c);

	void addVL(const VL &vl);
	void addVLs(const std::vector<VL> &vls);
	void removeVL(const VL &vl);
	void removeVLs(const std::vector<VL> &vls);
	void changeVL(const VL &vl, const VL &vl_new);
	void changeVLs(const std::vector<VL> &vls, const std::vector<VL> &vls_new);
	void removeHost(uint32_t id);
	Host host(uint32_t id);
	uint32_t switchesAmount();
private:
	VLSet vls;
	std::vector<Host> hosts;
	Component *app;

	void setRules(const std::vector<Settings> &settings);
};
