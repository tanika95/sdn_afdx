#include <vector>

#include "parametrs.hh"

#include "component.hh"
#include "../../../oflib/ofl-structs.h"


using namespace vigil;
using namespace vigil::container;

class VL {
public:
	VL(uint32_t vl_id, uint32_t s_id, uint32_t r_id, SLA prms,
		std::vector<Switch> swts, Component *c);
	VL();

	void add() const;
	void remove() const;
	SLA sla() const;
	uint32_t id() const;
	uint32_t sender() const;
	uint32_t receiver() const;
private:
	uint32_t vl_id;
	uint32_t sender_id;
	uint32_t receiver_id;
	SLA params;
	std::vector<Switch> switches;
	Component *app;

	void flowmod(enum ofp_flow_mod_command cmd, const Switch &swtch) const;
	void metermod(enum ofp_meter_mod_command cmd, const Switch &swtch) const;
};
