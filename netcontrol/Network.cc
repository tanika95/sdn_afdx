#include "Network.hh"

#include "Settings.hh"

using namespace vigil;
using namespace vigil::container;
using namespace std;

Network::Network(const VLSet &vls, Component *c)
	: vls(vls), app(c)
{
}

void Network::configure()
{
	for (uint32_t i = 0; i < vls.size(); i++) {
		cout << "LOG: add vl" << vls[i].id() << endl;
		setRules(vls[i].addSettings());
	}
}

void Network::addVL(const VL &vl)
{
	vls.push_back(vl);
	setRules(vl.addSettings());
}

void Network::addVLs(const vector<VL> &vlss)
{
	for(uint32_t i = 0; i < vlss.size(); i++) {
		addVL(vlss[i]);
	}
}

void Network::setRules(vector<Settings> settings)
{
	for (uint32_t i = 0; i < settings.size(); i++) {
		app->send_openflow_msg(settings[i].id(), settings[i].firstMessage(), 0, true);
		app->send_openflow_msg(settings[i].id(), settings[i].secondMessage(), 0, true);
	}
}

void Network::removeVL(const VL &vl)
{
	topo.removeVlFromHost(vl);
	setRules(vl.removeSettings());
	vls[vl.id()] = VL();
}
void Network::removeVLs(const VLSet &vlss)
{
	for(uint32_t i = 0; i < vlss.size(); i++) {
		removeVL(vlss[i]);
	}
}

void Network::changeVL(const VL &vl)
{
	setRules(vls[vl.id()].changeSettings(vl));
	vls[vl.id()] = vl;
}

void Network::changeVLs(const VLSet &vls_new)
{
	for(uint32_t i = 0; i < vls_new.size(); i++) {
		changeVL(vls_new[i]);
	}
}

VLSet Network::vlTable() const
{
	for(uint32_t i = 0; i < vls.size(); i++) {
		vls[i].show();
	}
	return vls;
}
