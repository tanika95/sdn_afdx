#pragma once

#include <vector>
#include "vl.hh"

class Host {
	bool alive;
	std::vector<uint32_t> out_vl_ids;
	std::vector<uint32_t> in_vl_ids;
public:
	std::vector<uint32_t> incomingVlIds();
	std::vector<uint32_t> outcomingVlIds();
	void addIncoming(const VL &vl);
	void addOutcoming(const VL &vl);
	void removeIncoming(const VL &vl);
	void removeOutcoming(const VL &vl);
	void die();
};
