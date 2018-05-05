#include "Switch.hh"

Switch::Switch(uint32_t id, uint32_t in, uint32_t out)
	: sw_id(id), in_port(in), out_port(out)
{}

uint32_t Switch::id() const
{
	return sw_id;
}

uint32_t Switch::in() const
{
	return in_port;
}

uint32_t Switch::out() const
{
	return out_port;
}
