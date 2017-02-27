#include <stdint.h>
#include <iostream>

class Switch {
public:
	Switch(double jitt, uint32_t id);

	double jswitch() const;
	uint32_t id() const;
private:
	double jitter;
	uint32_t sw_id;
};

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
