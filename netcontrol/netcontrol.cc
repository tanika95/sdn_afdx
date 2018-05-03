#include <network.hh>


#include <boost/bind.hpp>
#include <unistd.h>
#include "datapath-join.hh"

using namespace vigil;
using namespace vigil::container;

class netcontrol : public Component {
        Network network;
        uint32_t switches_num;
        Network topology() {
                std::vector<Host> hosts;
                hosts.push_back(Host());
                hosts.push_back(Host());
                hosts.push_back(Host());
                return Network(VLSet(), hosts, 3);
        }

        VL vl1() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 1, 1, 3));
                swts.push_back(Switch(jitt, 3, 2, 1));
                return VL(1, 1, 0, SLA(1, 1200), swts, this);
        }

        VL vl2() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 1, 1, 2));
                swts.push_back(Switch(jitt, 2, 2, 3));
                swts.push_back(Switch(jitt, 3, 3, 1));
                return VL(2, 1, 0, SLA(1, 800), swts, this);
        }

        VL vl3() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 2, 1, 3));
                swts.push_back(Switch(jitt, 3, 3, 1));
                return VL(3, 1, 0, SLA(1, 800), swts, this);
        }

        VL vl1new() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 1, 1, 2));
                swts.push_back(Switch(jitt, 2, 2, 3));
                swts.push_back(Switch(jitt, 3, 3, 1));
                return VL(1, 1, 0, SLA(1, 1200), swts, this);
        }

        void scenario() {
                std::cout << "LOG: Starting scenario 3.A" << std::endl;
                VL vl = vl1();
                network.addVL(vl);
                network.addVL(vl2());
                network.addVL(vl3());
                char now;
                std::cin >> now;
                std::cout << "LOG: s1-s3 break" << std::endl;
                network.removeVL(vl);
                network.addVL(vl1new());
        }
public:
        netcontrol(const Context* c, const json_object*)
                : Component(c), network(topology()), switches_num(0)
        {}

        void configure(const Configuration*) {
        }

        void install() {
                register_handler(Datapath_join_event::static_get_name(), boost::bind(&netcontrol::handler, this, _1));
        }

        Disposition handler (const Event& e) {
                switches_num++;
                if (switches_num != network.switchesAmount()) {
                        return CONTINUE;
                }
                scenario();
                return STOP;
        }
	reload()
	{
		VlSet vls;
		try {
			vls = Algotithm.run();
		catch (const exception &e) {
			// log algorithm failed
			return;
		}
		apply(vls);
	}

	breakComm()
	{
		map.breakComm();
		reload();
	}

	breakLink()
	{
		map.breakLink();
		reload();
	}

};

REGISTER_COMPONENT(container::Simple_component_factory<netcontrol>, netcontrol);
