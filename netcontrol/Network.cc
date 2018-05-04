#include "Network.hh"

#include <algorithm>
#include "Settings.hh"

using namespace vigil;
using namespace std;

Network::Network(const VLSet &vls, const std::vector<Host> &hsts, Component *c)
	: vls(vls), hosts(hsts), switches_amount(amount), app(c)
{}

void Network::addVL(const VL &vl)
{
	vls.add(vl);
	setRules(vl.addSettings());
	hosts[vl.sender()].addOutcoming(vl);
	hosts[vl.receiver()].addIncoming(vl);
}

void Network::setRules(const vector<Settings> &settings)
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
	hosts[vl.sender()].removeOutcoming(vl);
	hosts[vl.receiver()].removeIncoming(vl);
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
