#include "Settings.hh"

using namespace vigil;

Settings::Settings(uint32_t id, ofl_msg_flow_mod flow, ofl_msg_meter_mod meter, bool mode)
		: swtch_id(id), flow_msg(flow), meter_msg(meter), add(mode)
{
}

datapathid Settings::id()
{
	return datapathid().from_host(swtch_id);
}

struct ofl_msg_header *Settings::firstMessage()
{
	if (add) {
		return (struct ofl_msg_header *)&meter_msg;
	} else {
		return (struct ofl_msg_header *)&flow_msg;
	}
}

struct ofl_msg_header *Settings::secondMessage()
{
	if (add) {
		return (struct ofl_msg_header *)&flow_msg;
	} else {
		return (struct ofl_msg_header *)&meter_msg;
	}
}
