#pragma once

#include <unistd.h>
#include "component.hh"
#include "datapath-join.hh"
#include "Config.hh"
#include "Network.hh"
#include "Topology.hh"
#include "Vl.hh"

using namespace vigil;
using namespace vigil::container;

class Netcontrol : public Component {
public:
        Netcontrol(const Context* c, const json_object*);

        void configure(const Configuration*);
        void install();
        Disposition handler (const Event& e);
	void breakComm(uint32_t s1);
	void breakLink(uint32_t s1, uint32_t s2);
private:
	Network network;
	Topology map;
	uint32_t switches_online;

	Network init();
	void scenario();
	void apply(const VLSet &vls);
	void reload();

};
