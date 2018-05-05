#pragma once

#include <unistd.h>
#include "component.hh"
#include "datapath-join.hh"
#include "Network.hh"
#include "Topology.hh"
#include "Vlset.hh"

using namespace vigil;
using namespace vigil::container;

class Netcontrol : public Component {
public:
        Netcontrol(const Context* c, const json_object*);

        void configure(const Configuration*);
        void install();
        Disposition handler (const Event& e);
	void breakComm();
	void breakLink();
private:
	Network network;
	uint32_t switches_num;
        Topology map;


	Network init();
	void scenario();
	void apply(const VLSet &vls);
	void reload();

};
