#include "Vl.hh"

#include "openflow-default.hh"
#include <unistd.h>
#include "flowmod.hh"

using namespace vigil;
using namespace std;

VL::VL(uint32_t v_id, uint32_t s_id, uint32_t r_id, SLA prms,
	Route swts)
		: vl_id(v_id), sender_id(s_id), receiver_id(r_id),
		params(prms), switches(swts)
{}

VL::VL(const VL &vl, const Route &swts)
	: vl_id(vl.id()), sender_id(vl.sender()), receiver_id(vl.receiver()),
	params(vl.sla()), switches(swts)
{}


VL::VL()
{}

vector<Settings> VL::settings(bool add, const Route &swtchs) const
{
	vector<Settings> settings;
	for(uint32_t i = 0; i < swtchs.size(); i++) {
		settings.push_back(
			Settings(
				swtchs[i].id(),
				flowmod(add, swtchs[i]),
				metermod(add, swtchs[i]),
				add
			)
		);
	}
	return settings;
}


vector<Settings> VL::addSettings() const
{
	return settings(true, switches);
}

vector<Settings> VL::removeSettings() const
{
	return settings(false, switches);
}

vector<Settings> VL::changeSettings(const VL &vl) const
{
	Route path = vl.changedPath(switches);
	return settings(false, switches);
}

Route VL::changedPath(const Route &sw) const
{
	return switches;
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

SLA VL::sla() const
{
	return params;
}

double VL::bw() const
{
	return params.lmax() / params.bag();
}

void VL::show() const
{
	cout << "Link " << vl_id << endl;
	cout << "Sender: " << sender_id << " Receiver: " << receiver_id<< '\n';
	cout << "Route:" << endl;
	for(uint32_t i = 0; i < switches.size(); i++) {
		cout << "switch " << switches[i].id() << "ports "
			<< switches[i].in() << ":" << switches[i].out()<< endl;
	}
	cout << endl << endl;
}

ofl_msg_flow_mod VL::flowmod(bool add, const Switch &swtch) const
{
	ofp_flow_mod_command cmd = add ? OFPFC_ADD : OFPFC_DELETE;
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

ofl_msg_meter_mod VL::metermod(bool add, const Switch &swtch) const
{
	ofp_meter_mod_command cmd = add ? OFPMC_ADD : OFPMC_DELETE;
	struct ofl_meter_band_header band;
	band.type = OFPMBT_DROP;
	band.rate = params.lmax() / params.bag();
	band.burst_size = params.lmax() * (1 + (params.jswitch() / params.bag()));

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
