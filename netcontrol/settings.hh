#include "../../../oflib/ofl-structs.h"

class Settings
{
public:
	Settings(uint32_t id, ofl_msg_flow_mod flow, ofl_msg_meter_mod meter,
		ofp_flow_mod_command cmd);

	datapathid id();
	struct ofl_msg_header* firstMessage();
	struct ofl_msg_header* secondMessage();
private:
	uint32_t swtch_id;
	ofl_msg_flow_mod flow_msg;
	ofl_msg_meter_mod meter_msg;
	ofp_flow_mod_command mode;
};
