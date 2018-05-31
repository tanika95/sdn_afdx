#pragma once

#include <boost/property_map/property_map.hpp>
#include "Topology.hh"
#include "Vl.hh"

class Algorithm
{
public:
	Algorithm(VLSet vls, Topology topo);
	VLSet run();
	VLSet initial();
	Topology updateTopo();
private:
	VLSet links;
	Topology map;

	VLSet baseStep();
	VLSet additionalStep();
	VL searchPath(const VL &vl, uint32_t from, uint32_t to);
};
