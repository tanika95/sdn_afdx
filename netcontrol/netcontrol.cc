#include <netcontrol.hh>


#include <boost/bind.hpp>
#include <unistd.h>
#include "datapath-join.hh"

using namespace vigil;
using namespace vigil::container;

Netcontrol::Netcontrol(const Context* c, const json_object*)
        : Component(c), network(init()), switches_num(0)
{}

Network Netcontrol::init()
{
        std::vector<Host> hosts;
        hosts.push_back(Host());
        hosts.push_back(Host());
        hosts.push_back(Host());
        return Network(Algorithm().initial(), hosts, this);
}


void Netcontrol::scenario()
{
        std::cout << "LOG: Starting scenario" << std::endl;
}

void Netcontrol::apply() {
        std::cout << "LOG: New configuration applied" << std::endl;
}

void Netcontrol::breakComm()
{
	std::cout << "LOG: Commutator broken" << std::endl;
	map.breakComm();
	reload();
}

void Netcontrol::breakLink()
{
	std::cout << "LOG: Link broken" << std::endl;
	map.breakLink();
	reload();
}

void Netcontrol::reload()
{
	VlSet vls;
	try {
		vls = Algotithm.run();
	} catch (const exception &e) {
		std::cout << "LOG: New VL's configuration can't be created" << std::endl;
		return;
	}
	std::cout << "LOG: New VL's configuration created" << std::endl;
	apply(vls);
}

void Netcontrol::configure(const Configuration*)
{
}

void Netcontrol::install()
{
        register_handler(Datapath_join_event::static_get_name(),
		boost::bind(&netcontrol::handler, this, _1));
}

Disposition Netcontrol::handler(const Event& e)
{
        switches_num++;
        if (switches_num != network.switchesAmount()) {
                return CONTINUE;
        }
        scenario();
        return STOP;
}


REGISTER_COMPONENT(container::Simple_component_factory<Netcontrol>, Netcontrol);
