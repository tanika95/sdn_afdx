#include "Sla.hh"

SLA::SLA()
{}

SLA::SLA(double bag, double lmax, double jitt)
	: bandwidth_allocation_gap(bag), max_packet_length(8 * lmax / 1000), jitter(jitt)
{}

double SLA::bag() const
{
	return bandwidth_allocation_gap;
}
double SLA::lmax() const
{
	return max_packet_length;
}

double SLA::jswitch() const
{
	return jitter;
}
