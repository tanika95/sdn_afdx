#pragma once

#include <map>
#include "vl.hh"


class VLSet {
public:
	void add(const VL &vl);
	void remove(uint32_t id);
	VL vl(uint32_t id);
private:
	std::map<uint32_t, VL> vls;
};
