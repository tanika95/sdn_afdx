#include "Link.hh"

using namespace std;

Link::Link(uint32_t sw1, uint32_t sw2, uint32_t p1, uint32_t p2, double bws)
	: s1(sw1), s2(sw2), port1(p1), port2(p2), bw(bws), availible_bw(bws)
{}

Link::Link()
{}

void Link::addVL(const VL &vl)
{
	vls.push_back(vl.id());
}
