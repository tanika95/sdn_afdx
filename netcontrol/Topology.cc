#include "Topology.hh"

using namespace std;

Topology::Topology(map<uint32_t, Host> hst, uint32_t switches, Links lnks)
		: hosts(hst), swtch_num(switches), links(lnks)
{}

void Topology::breakLink(uint32_t s1, uint32_t s2)
{
	broken[make_pair(s1, s2)] = links[make_pair(s2, s1)];
	broken[make_pair(s2, s1)] = links[make_pair(s2, s1)];
	links.erase(make_pair(s1, s2));
	links.erase(make_pair(s2, s1));
}

void Topology::breakComm(uint32_t s1)
{
	Links::iterator it;
	for (uint32_t i = 0; i < swtch_num; i++) {
		it = links.find(make_pair(s1, i));
	  	if (it != links.end()) {
			links.erase (it);
		}
		it = links.find(make_pair(i, s1));
	  	if (it != links.end()) {
			links.erase (it);
		}
	}
}

void Topology::breakHost(uint32_t id)
{
	hosts[id].die();
}

void Topology::reloaded()
{
	broken.clear();
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
	return swtch_num;
}

Graph Topology::graphForVL(const VL &vl) const
{
	Edge edgs[links.size()];
	int bdws[links.size()];
	int j = 0;
	for (Links::const_iterator it = links.begin(); it != links.end(); ++it) {
		Link link = it->second;
		if (vl.bw() <= link.availible_bw) {
			edgs[j] = Edge(link.s1, link.s2);
			bdws[j] = link.availible_bw;
			j++;
		}
	}
	return Graph(edgs, edgs + j, bdws, swtch_num + hosts.size());
}

uint32_t Topology::port(uint32_t from, uint32_t to)
{
	return links[make_pair(from, to)].port1;
}

void Topology::decreaseBw(double bw, uint32_t from, uint32_t to)
{
	links[make_pair(from, to)].availible_bw -= bw;
}

State Topology::stateForVL(const VL &vl) const
{
	for (Links::const_iterator it = broken.begin(); it != broken.end(); ++it) {
		Link link = it->second;
		if (find(link.vls.begin(), link.vls.end(), vl.id()) != link.vls.end()) {
			return State(true, link.s1, link.s2);
		}
	}
	return State(false, 0, 0);
}
