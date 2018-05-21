#pragma once

#include <stdint.h>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include "Vl.hh"

class Link {
public:
	Link(uint32_t sw1, uint32_t sw2, uint32_t p1, uint32_t p2, double bws);
	Link();
	void addVL(const VL& vl);
	uint32_t s1;
	uint32_t s2;
	uint32_t port1;
	uint32_t port2;
	double bw;
	double availible_bw;
	std::vector<uint32_t> vls;
};

typedef std::map<std::pair<uint32_t, uint32_t>, Link> Links;
