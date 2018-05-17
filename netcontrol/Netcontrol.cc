#include <Netcontrol.hh>

#include <boost/bind.hpp>
#include <unistd.h>
#include "datapath-join.hh"
#include "Algorithm.hh"
#include "Vl.hh"

using namespace std;
using namespace vigil;
using namespace vigil::container;

Netcontrol::Netcontrol(const Context* c, const json_object*)
        : Component(c), config("netc.xml"), network(init()), switches_num(0)
{}

Network Netcontrol::init()
{
        Topology map = config.topology();
        VLSet vls = Algorithm(config.dataflows(), map).initial();
        return Network(vls, map, this);
}


void Netcontrol::scenario()
{
        std::cout << "LOG: Starting scenario" << std::endl;
}

void Netcontrol::apply(const VLSet &vls)
{
	network.changeVLs(vls);
        std::cout << "LOG: New configuration applied" << std::endl;
}

void Netcontrol::breakComm()
{
	std::cout << "LOG: Commutator broken" << std::endl;
	network.breakComm();
	reload();
}

void Netcontrol::breakLink()
{
	std::cout << "LOG: Link broken" << std::endl;
	network.breakLink();
	reload();
}

void Netcontrol::reload()
{
	VLSet vls;
	try {
		vls = Algorithm(network.vlTable(), network.map()).run();
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
		boost::bind(&Netcontrol::handler, this, _1));
}

Disposition Netcontrol::handler(const Event& e)
{
        switches_num++;
        if (switches_num != network.map().switchesAmount()) {
                return CONTINUE;
        }
        scenario();
        return STOP;
}


REGISTER_COMPONENT(container::Simple_component_factory<Netcontrol>, Netcontrol);
