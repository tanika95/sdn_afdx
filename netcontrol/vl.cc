#include "vl.hh"

#include "openflow-default.hh"
#include <unistd.h>
#include "flowmod.hh"

using namespace vigil;
using namespace std;

VL::VL(uint32_t v_id, uint32_t s_id, uint32_t r_id, SLA prms,
	std::vector<Switch> swts)
		: vl_id(v_id), sender_id(s_id), receiver_id(r_id),
		params(prms), switches(swts)
{}

VL::VL()
{}

vector<Settings> VL::settings(enum ofp_flow_mod_command cmd, const vector<Switch> &swtchs) const
{
	vector<Settings> settings;
	for(uint32_t i = 0; i < swtchs.size(); i++) {
		settings.push_back(
			Settings(
				flowmod(cmd, swtchs[i]),
				metermod(cmd swtchs[i]),
				cmd
			)
		);
	}
	return settings;
}


vector<Settings> VL::addSettings() const
{
	settings(OFPMC_ADD, switches);
}

vector<Settings> VL::removeSettings() const
{
	settings(OFPMC_DELETE, switches);
}


SLA VL::sla() const
{
	return params;
}

uint32_t VL::id() const
{
	return vl_id;
}

uint32_t VL::sender() const
{
	return sender_id;
}

uint32_t VL::receiver() const
{
	return receiver_id;
}

ofl_msg_flow_mod VL::flowmod(enum ofp_flow_mod_command cmd, const Switch &swtch) const
{
	Flow f;
	f.Add_Field("in_port", swtch.in());
	f.Add_Field("vlan_id", vl_id);
	FlowMod *mod = new FlowMod(cmd, ofd_flow_mod_flags());
	Actions *acts = new Actions();
	Instruction *inst =  new Instruction();
	acts->CreateOutput(swtch.out());
	inst->CreateApply(acts);
	inst->CreateMeterInstruction(vl_id);
	mod->AddMatch(&f.match);
	mod->AddInstructions(inst);

	return mod->fm_msg;
}

ofl_msg_meter_mod VL::metermod(enum ofp_meter_mod_command cmd, const Switch &swtch) const
{
	struct ofl_meter_band_header band;
	band.type = OFPMBT_DROP;
	band.rate = sla().lmax() / sla().bag();
	band.burst_size = sla().lmax() * (1 + (swtch.jswitch() / sla().bag()));

	struct ofl_msg_meter_mod msg;
	msg.header.type = OFPT_METER_MOD;
	msg.command = cmd;
	msg.flags = OFPMF_PKTPS || OFPMF_BURST;
	msg.meter_id = vl_id;
	msg.meter_bands_num = 1;
	msg.bands = (struct ofl_meter_band_header **)
		malloc(msg.meter_bands_num * sizeof(struct ofl_meter_band_header *));
	msg.bands[0] = &band;

	return msg;
}
