#include "network.hh"

#include <algorithm>

using namespace std;

vector<uint32_t> Host::incomingVlIds() {
	return in_vl_ids;
}

vector<uint32_t> Host::outcomingVlIds() {
	return out_vl_ids;
}

void Host::addIncoming(const VL &vl) {
	in_vl_ids.push_back(vl.id());
}

void Host::addOutcoming(const VL &vl) {
	out_vl_ids.push_back(vl.id());
}

void Host::removeIncoming(const VL &vl) {
	in_vl_ids.erase(
		remove(in_vl_ids.begin(), in_vl_ids.end(), vl.id()), in_vl_ids.end());
}

void Host::removeOutcoming(const VL &vl) {
	out_vl_ids.erase(
		remove(out_vl_ids.begin(), out_vl_ids.end(), vl.id()), out_vl_ids.end());
}

void Host::die() {
	alive = false;
}

Network::Network(const VLSet &vls, const std::vector<Host> &hsts, uint32_t amount)
	: vls(vls), hosts(hsts), switches_amount(amount)
{}

void Network::addVL(const VL &vl) {
	vls.add(vl);
	hosts[vl.sender()].addOutcoming(vl);
	hosts[vl.receiver()].addIncoming(vl);
}

void Network::addVLs(const vector<VL> &vls) {
	for(uint32_t i = 0; i < vls.size(); i++) {
		addVL(vls[i]);
	}
}

void Network::removeVL(const VL &vl) {
	hosts[vl.sender()].removeOutcoming(vl);
	hosts[vl.receiver()].removeIncoming(vl);
	vls.remove(vl.id());
}
void Network::removeVLs(const std::vector<VL> &vls) {
	for(uint32_t i = 0; i < vls.size(); i++) {
		removeVL(vls[i]);
	}
}
void Network::removeHost(uint32_t id) {
	hosts[id].die();
}

Host Network::host(uint32_t id) {
	return hosts[id];
}

uint32_t Network::switchesAmount() {
	return switches_amount;
}
