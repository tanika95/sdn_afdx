#include "vl.hh"

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_array.hpp>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <stdint.h>
#include <iostream>

#include "openflow-default.hh"
#include "assert.hh"
#include "flow.hh"
#include "fnv_hash.hh"
#include "hash_set.hh"
#include "ofp-msg-event.hh"
#include "vlog.hh"
#include "flowmod.hh"
#include "datapath-join.hh"
#include <stdio.h>

#include <stdio.h>
#include "netinet++/datapathid.hh"
#include "netinet++/ethernetaddr.hh"
#include "netinet++/ethernet.hh"

#include "../../../oflib/ofl-actions.h"
#include "../../../oflib/ofl-structs.h"
#include "../../../oflib/ofl-messages.h"

using namespace vigil;
using namespace vigil::container;
using namespace std;

VL::VL(int v_id, int s_id, int r_id, SLA prms, std::vector<Switch> swts, Component *c)
	: vl_id(v_id) , sender_id(s_id) , receiver_id(r_id) , params(prms)
	, switches (swts) , app(c)
{}

VL::VL()
{}

void VL::add() const {
	Flow  f;
	uint32_t in_port = sender_id + 1;
	uint32_t out_port = receiver_id + 1;
	f.Add_Field("in_port", in_port);
	Actions *acts = new Actions();
	acts->CreateOutput(out_port);
	Instruction *inst =  new Instruction();
	inst->CreateApply(acts);
	FlowMod *mod = new FlowMod(0x00ULL,0x00ULL, 0,OFPFC_ADD, 1, OFP_FLOW_PERMANENT, OFP_DEFAULT_PRIORITY,0xffffffff, OFPP_ANY, OFPG_ANY, ofd_flow_mod_flags());
	mod->AddMatch(&f.match);
	mod->AddInstructions(inst);
	datapathid id = datapathid().from_host(1);
	app->send_openflow_msg(id, (struct ofl_msg_header *)&mod->fm_msg, 0/*xid*/, true/*block*/);
	std::cout << "/* message */" << '\n';
}

void VL::remove() const {

}

SLA VL::sla() const {
	return params;
}

int VL::id() const {
	return vl_id;
}

int VL::sender() const {
	return sender_id;
}

int VL::receiver() const {
	return receiver_id;
}

void VLSet::add(const VL &vl) {
	vl.add();
	vls[vl.id()] = vl;
}

void VLSet::remove(int id) {
	vls[id].remove();
	vls.erase(id);
}

VL VLSet::vl(int id) {
	return vls[id];
}
