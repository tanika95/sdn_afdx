#include "Host.hh"
#include <algorithm>

using namespace std;

Host::Host()
	: alive(true)
{}

vector<uint32_t> Host::incomingVlIds()
{
	return in_vl_ids;
}

vector<uint32_t> Host::outcomingVlIds()
{
	return out_vl_ids;
}

void Host::addIncoming(const VL &vl)
{
	in_vl_ids.push_back(vl.id());
}

void Host::addOutcoming(const VL &vl)
{
	out_vl_ids.push_back(vl.id());
}

void Host::removeIncoming(const VL &vl)
{
	in_vl_ids.erase(
		remove(in_vl_ids.begin(), in_vl_ids.end(), vl.id()), in_vl_ids.end());
}

void Host::removeOutcoming(const VL &vl)
{
	out_vl_ids.erase(
		remove(out_vl_ids.begin(), out_vl_ids.end(), vl.id()), out_vl_ids.end());
}

void Host::die()
{
	alive = false;
}
