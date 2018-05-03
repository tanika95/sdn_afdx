#include "network.hh"

#include <algorithm>

using namespace std;

Network::Network(const VLSet &vls, const std::vector<Host> &hsts)
	: vls(vls), hosts(hsts), switches_amount(amount)
{}

void Network::addVL(const VL &vl)
{
	vls.add(vl);
	hosts[vl.sender()].addOutcoming(vl);
	hosts[vl.receiver()].addIncoming(vl);
}

void Network::addVLs(const vector<VL> &vlss)
{
	for(uint32_t i = 0; i < vlss.size(); i++) {
		addVL(vlss[i]);
	}
}

void Network::removeVL(const VL &vl)
{
	hosts[vl.sender()].removeOutcoming(vl);
	hosts[vl.receiver()].removeIncoming(vl);
	vls.remove(vl.id());
}
void Network::removeVLs(const std::vector<VL> &vlss)
{
	for(uint32_t i = 0; i < vlss.size(); i++) {
		removeVL(vlss[i]);
	}
}

void Network::changeVL(const VL &vl, const VL &vl_new)
{
	vls.remove(vl.id());
	vls.add(vl_new);
}

void Network::changeVLs(const std::vector<VL> &vlss, const std::vector<VL> &vls_new)
{
	for(uint32_t i = 0; i < vlss.size(); i++) {
		changeVL(vls.vl(vlss[i].id()), vlss[i]);
	}
}

void Network::removeHost(uint32_t id)
{
	hosts[id].die();
}

Host Network::host(uint32_t id)
{
	return hosts[id];
}

uint32_t Network::switchesAmount()
{
	return hosts.size();
}
