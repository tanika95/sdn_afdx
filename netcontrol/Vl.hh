#pragma once

#include <vector>
#include "../../../oflib/ofl-structs.h"
#include "Settings.hh"
#include "Sla.hh"
#include "Switch.hh"

class VL {
public:
	VL(uint32_t vl_id, uint32_t s_id, uint32_t r_id, SLA prms,
		Route swts = Route());
	VL();

	std::vector<Settings> addSettings() const;
	std::vector<Settings> removeSettings() const;
	std::vector<Settings> changeSettings(const VL &vl) const;
	std::pair<Route, Route> changedPath(const Route &sw) const;
	uint32_t id() const;
	uint32_t sender() const;
	uint32_t receiver() const;
private:
	uint32_t vl_id;
	uint32_t sender_id;
	uint32_t receiver_id;
	SLA params;
	Route switches;

	ofl_msg_flow_mod flowmod(bool add, const Switch &swtch) const;
	ofl_msg_meter_mod metermod(bool add, const Switch &swtch) const;
	std::vector<Settings> settings(bool add, const Route &swtchs) const;
};

typedef std::vector<VL> VLSet;
