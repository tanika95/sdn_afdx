#include <vector>

#include "parametrs.hh"
#include "settings.hh"

#include "../../../oflib/ofl-structs.h"


class VL {
public:
	VL(uint32_t vl_id, uint32_t s_id, uint32_t r_id, SLA prms,
		std::vector<Switch> swts);
	VL();

	std::vector<Settings> addSettings() const;
	std::vector<Settings> removeSettings() const;
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

	ofl_msg_flow_mod flowmod(enum ofp_flow_mod_command cmd, const Switch &swtch) const;
	ofl_msg_meter_mod metermod(enum ofp_meter_mod_command cmd, const Switch &swtch) const;
	std::vector<Settings> settings(enum ofp_flow_mod_command cmd,
		const std::vector<Switch> &swtchs) const;
};
