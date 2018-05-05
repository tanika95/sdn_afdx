#pragma once

#include <vector>
#include <stdint.h>
#include <boost/graph/adjacency_list.hpp>
#include "Host.hh"
#include "Vl.hh"

class Topology
{
public:
	uint32_t switchesAmount() const;

	void breakLink();
	void breakComm();
	void breakHost(uint32_t id);

	void addVlToHost(const VL &vl);
	void removeVlFromHost(const VL &vl);
private:
	std::vector<Host> hosts;
};
