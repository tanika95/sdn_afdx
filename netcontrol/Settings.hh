#pragma once

#include "netinet++/datapathid.hh"
#include "../../../oflib/ofl-structs.h"
#include "flowmod.hh"

using namespace vigil;

class Settings
{
public:
	Settings(uint32_t id, ofl_msg_flow_mod flow, ofl_msg_meter_mod meter, bool mode);

	datapathid id();
	struct ofl_msg_header* firstMessage();
	struct ofl_msg_header* secondMessage();
private:
	uint32_t swtch_id;
	ofl_msg_flow_mod flow_msg;
	ofl_msg_meter_mod meter_msg;
	bool add;
};
