#include "network.hh"

#include <algorithm>

using namespace std;

vector<int> Host::incomingVlIds() {
	return in_vl_ids;
}

vector<int> Host::outcomingVlIds() {
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

Network::Network(const VLSet &vls, const std::vector<Host> &hsts)
	: vls(vls) , hosts(hsts)
{}

void Network::addVL(const VL &vl) {
	vls.add(vl);
	hosts[vl.sender()].addOutcoming(vl);
	hosts[vl.receiver()].addIncoming(vl);
}

void Network::addVLs(const vector<VL> &vls) {
	for(int i = 0; i < vls.size(); i++) {
		addVL(vls[i]);
	}
}

void Network::removeVL(const VL &vl) {
	hosts[vl.sender()].removeOutcoming(vl);
	hosts[vl.receiver()].removeIncoming(vl);
}
void Network::removeVLs(const std::vector<VL> &vls) {
	for(int i = 0; i < vls.size(); i++) {
		removeVL(vls[i]);
	}
}
void Network::removeHost(int id) {
	hosts[id].die();
}

Host Network::host(int id) {
	return hosts[id];
}
