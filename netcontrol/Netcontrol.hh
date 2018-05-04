#pragma once

#include <Network.hh>

#include <unistd.h>
#include "datapath-join.hh"

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


	Network init();
	void scenario();
	void apply();
	void reload();

};
