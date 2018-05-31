#pragma once

#include <vector>
#include "component.hh"
#include "Vl.hh"

using namespace vigil;
using namespace vigil::container;


class Network {
public:
	Network(const VLSet &vls, Component *c);

	VLSet vlTable() const;

	void addVL(const VL &vl);
	void addVLs(const VLSet &vls);
	void removeVL(const VL &vl);
	void removeVLs(const VLSet &vls);
	void changeVL(const VL &vl);
	void changeVLs(const VLSet &vls_new);
	void configure();
private:
	VLSet vls;
	Component *app;

	void setRules(std::vector<Settings> settings);
};
