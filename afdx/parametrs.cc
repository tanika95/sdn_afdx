#include "parametrs.hh"

int SLA::bag() {
	return bandwidth_allocation_gap;
}
int SLA::lmax() {
	return max_packet_length;
}

int Switch::jswitch() {
	return jitter;
}
