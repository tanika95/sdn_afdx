#include "vl.hh"

#include "openflow-default.hh"
#include <unistd.h>
#include "flowmod.hh"
#include "netinet++/datapathid.hh"

using namespace vigil;
using namespace std;

VL::VL(uint32_t v_id, uint32_t s_id, uint32_t r_id, SLA prms,
	std::vector<Switch> swts, Component *c)
	: vl_id(v_id), sender_id(s_id), receiver_id(r_id),
	params(prms), switches (swts), app(c)
{}

VL::VL()
{}

void VL::add() const {
	for(uint32_t i = 0; i < switches.size(); i++) {
		cout << "LOG: Adding vl to switch " << switches[i].id()<<endl;
		metermod(OFPMC_ADD, switches[i]);
		flowmod(OFPFC_ADD, switches[i]);
	}
}

void VL::remove() const {
	for(uint32_t i = 0; i < switches.size(); i++) {
		cout << "LOG: Deleting vl from switch " << switches[i].id()<<endl;
		flowmod(OFPFC_DELETE, switches[i]);
		metermod(OFPMC_DELETE, switches[i]);
	}
}

SLA VL::sla() const {
	return params;
}

uint32_t VL::id() const {
	return vl_id;
}

uint32_t VL::sender() const {
	return sender_id;
}

uint32_t VL::receiver() const {
	return receiver_id;
}

void VL::flowmod(enum ofp_flow_mod_command cmd, const Switch &swtch) const {
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

	std::cout << "LOG: VL id " << vl_id <<std::endl;
	app->send_openflow_msg(datapathid().from_host(swtch.id()),
		(struct ofl_msg_header *)&mod->fm_msg, 0, true);
	std::cout << "LOG: DONE"<<std::endl;
}

void VL::metermod(enum ofp_meter_mod_command cmd, const Switch &swtch) const {
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

	std::cout << "LOG: burst_size " << band.burst_size<<std::endl;
	std::cout << "LOG: rate " << band.rate <<std::endl;
	app->send_openflow_msg(datapathid().from_host(swtch.id()),
		(struct ofl_msg_header *)&msg, 0, true);
	std::cout << "LOG: DONE"<<std::endl;
}

void VLSet::add(const VL &vl) {
	vl.add();
	vls[vl.id()] = vl;
}

void VLSet::remove(uint32_t id) {
	vls[id].remove();
	vls.erase(id);
}

VL VLSet::vl(uint32_t id) {
	return vls[id];
}
