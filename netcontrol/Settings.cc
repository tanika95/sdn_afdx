#include "Settings.hh"

Settings::Settings(uint32_t id, ofl_msg_flow_mod flow, ofl_msg_meter_mod meter,
	ofp_flow_mod_command cmd)
		: swtch_id(id), flow_msg(flow), meter_msg(meter), mode(cmd)
{
}

datapathid Settings::id()
{
	return datapathid().from_host(swtch_id);
}

struct ofl_msg_header *Settings::firstMessage()
{
	if (mode == OFPMC_ADD) {
		return (struct ofl_msg_header *)&meter_msg;
	} else {
		return (struct ofl_msg_header *)&flow_msg;
	}
}

struct ofl_msg_header *Settings::secondMessage()
{
	if (mode == OFPMC_ADD) {
		return (struct ofl_msg_header *)&flow_msg;
	} else {
		return (struct ofl_msg_header *)&meter_msg;
	}
}
