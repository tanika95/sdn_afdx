#include "Topology.hh"

using namespace std;

void Topology::breakLink()
{
}

void Topology::breakComm()
{
}

void Topology::breakHost(uint32_t id)
{
	hosts[id].die();
}

void Topology::addVlToHost(const VL &vl)
{
	hosts[vl.sender()].addOutcoming(vl);
	hosts[vl.receiver()].addIncoming(vl);
}

void Topology::removeVlFromHost(const VL &vl)
{
	hosts[vl.sender()].removeOutcoming(vl);
	hosts[vl.receiver()].removeIncoming(vl);
}

uint32_t Topology::switchesAmount() const
{
}
