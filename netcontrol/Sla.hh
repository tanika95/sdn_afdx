#pragma once

#include <stdint.h>
#include <iostream>

class SLA {
public:
	SLA(double bag, double lmax, double jitt);
	SLA();

	double jswitch() const;
	double bag() const;
	double lmax() const;
private:
	double bandwidth_allocation_gap;
	double max_packet_length;
	double jitter;
};
