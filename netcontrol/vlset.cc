#include "vlset.hh"


void VLSet::add(const VL &vl)
{
	vl.add();
	vls[vl.id()] = vl;
}

void VLSet::remove(uint32_t id)
{
	vls[id].remove();
	vls.erase(id);
}

VL VLSet::vl(uint32_t id)
{
	return vls[id];
}
