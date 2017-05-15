#include "parametrs.hh"

Switch::Switch(double jitt, uint32_t id, uint32_t in, uint32_t out)
	: jitter(jitt), sw_id(id), in_port(in), out_port(out)
{}

double Switch::jswitch() const
{
	return jitter;
}

uint32_t Switch::id() const
{
	return sw_id;
}

uint32_t Switch::in() const
{
	return in_port;
}

uint32_t Switch::out() const
{
	return out_port;
}

SLA::SLA()
{}

SLA::SLA(double bag, double lmax)
	: bandwidth_allocation_gap(bag), max_packet_length(8 * lmax / 1000)
{}

double SLA::bag()
{
	return bandwidth_allocation_gap;
}
double SLA::lmax()
{
	return max_packet_length;
}
