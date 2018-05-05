#pragma once

#include "Topology.hh"
#include "Vlset.hh"

class Algorithm
{
public:
	Algorithm(VLSet vls, Topology topo);
	VLSet run();
	VLSet initial();
private:
	VLSet links;
	Topology map;

	VLSet baseStep();
	VLSet additionalStep();
};
