#include <Netcontrol.hh>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <unistd.h>
#include "datapath-join.hh"
#include "Algorithm.hh"
#include "Vl.hh"

using namespace std;
using namespace vigil;
using namespace vigil::container;

Netcontrol::Netcontrol(const Context* c, const json_object*)
        : Component(c), network(init()), switches_num(0)
{}

Network Netcontrol::init()
{
	Config config("/home/tanyaerm/netc.xml");
        Topology map = config.topology();
        VLSet vls = Algorithm(config.dataflows(), map).initial();
        return Network(vls, map, this);
}


void Netcontrol::scenario()
{
        network.configure();
        network.vlTable();
        std::cout << "LOG: Starting scenario" << std::endl;
        network.breakLink(2, 3);
}

void Netcontrol::apply(const VLSet &vls)
{
	network.changeVLs(vls);
        std::cout << "LOG: New configuration applied" << std::endl;
}

void Netcontrol::breakComm(uint32_t s1)
{
	std::cout << "LOG: Commutator broken" << std::endl;
	network.breakComm(s1);
	reload();
}

void Netcontrol::breakLink(uint32_t s1, uint32_t s2)
{
	std::cout << "LOG: Link broken" << std::endl;
	network.breakLink(s1, s2);
	reload();
}

void Netcontrol::reload()
{
	VLSet vls;
        boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();

	try {
		Algorithm alg = Algorithm(network.vlTable(), network.map());
                alg.run();
                network.updateTopo(alg.updateTopo());
	} catch (const exception &e) {
		std::cout << "LOG: New VL's configuration can't be created" << std::endl;
		return;
	}
	std::cout << "LOG: New VL's configuration created" << std::endl;
        boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
        boost::posix_time::time_duration diff = end - start;
        std::cout << "LOG: Took ms - " << diff.total_milliseconds() << std::endl;
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
