#pragma once

#include <stdint.h>
#include <iostream>

class Switch {
public:
	Switch(double jitt, uint32_t id, uint32_t in_port, uint32_t out_port);

	double jswitch() const;
	uint32_t id() const;
	uint32_t in() const;
	uint32_t out() const;
private:
	double jitter;
	uint32_t sw_id;
	uint32_t in_port;
	uint32_t out_port;
};
