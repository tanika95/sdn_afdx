#include "parametrs.hh"

Switch::Switch(double jitt, uint32_t id) : jitter(jitt), sw_id(id)
{}

double Switch::jswitch() const {
	return jitter;
}

uint32_t Switch::id() const {
	return sw_id;
}

SLA::SLA()
{}

SLA::SLA(double bag, double lmax) : bandwidth_allocation_gap(bag), max_packet_length(lmax)
{}

double SLA::bag() {
	return bandwidth_allocation_gap;
}
double SLA::lmax() {
	return max_packet_length;
}
