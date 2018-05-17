#pragma once

#include <stdint.h>
#include <iostream>

class Switch {
public:
	Switch(uint32_t id, uint32_t in_port, uint32_t out_port);

	uint32_t id() const;
	uint32_t in() const;
	uint32_t out() const;
private:
	uint32_t sw_id;
	uint32_t in_port;
	uint32_t out_port;
};

typedef std::vector<Switch> Route;
