#include "Network.hh"

#include "Settings.hh"

using namespace vigil;
using namespace vigil::container;
using namespace std;

Network::Network(const VLSet &vls, const Topology &map, Component *c)
	: vls(vls), topo(map), app(c)
{}

void Network::addVL(const VL &vl)
{
	vls.add(vl);
	setRules(vl.addSettings());
	topo.addVlToHost(vl);
}

void Network::setRules(vector<Settings> settings)
{
	for (uint32_t i = 0; i < settings.size(); i++) {
		app->send_openflow_msg(settings[i].id(), settings[i].firstMessage(), 0, true);
		app->send_openflow_msg(settings[i].id(), settings[i].secondMessage(), 0, true);
	}
}

void Network::addVLs(const vector<VL> &vlss)
{
	for(uint32_t i = 0; i < vlss.size(); i++) {
		addVL(vlss[i]);
	}
}

void Network::removeVL(const VL &vl)
{
	topo.removeVlFromHost(vl);
	setRules(vl.removeSettings());
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

VLSet Network::vlTable() const
{
	return vls;
}

Topology Network::map() const
{
	return topo;
}

void Network::breakComm()
{
	topo.breakComm();
}

void Network::breakLink()
{
	topo.breakLink();
}

void Network::breakHost(uint32_t id)
{
	topo.breakHost(id);
}
