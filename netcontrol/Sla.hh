#pragma once

#include <stdint.h>
#include <iostream>

class SLA {
public:
	SLA(double bag, double lmax);
	SLA();

	double bag();
	double lmax();
private:
	double bandwidth_allocation_gap;
	double max_packet_length;
};
