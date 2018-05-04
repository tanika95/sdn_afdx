#include "Sla.hh"

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
