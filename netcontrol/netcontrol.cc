#include <network.hh>


#include <boost/bind.hpp>
#include <unistd.h>
#include "datapath-join.hh"

using namespace vigil;
using namespace vigil::container;

class netcontrol : public Component {
        Network network;
        uint32_t switches_num;


        Network init() {
                std::vector<Host> hosts;
                hosts.push_back(Host());
                hosts.push_back(Host());
                hosts.push_back(Host());
                return Network(Algorithm().initial(), hosts, this);
        }


        void scenario() {
                std::cout << "LOG: Starting scenario" << std::endl;
        }

	void apply() {
                std::cout << "LOG: New configuration applied" << std::endl;
        }

	void reload()
	{
		VlSet vls;
		try {
			vls = Algotithm.run();
		catch (const exception &e) {
			std::cout << "LOG: New VL's configuration can't be created" << std::endl;
			return;
		}
	        std::cout << "LOG: New VL's configuration created" << std::endl;
		apply(vls);
	}
public:
        netcontrol(const Context* c, const json_object*)
                : Component(c), network(init()), switches_num(0)
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

	void breakComm()
	{
		std::cout << "LOG: Commutator broken" << std::endl;
		map.breakComm();
		reload();
	}

	void breakLink()
	{
		std::cout << "LOG: Link broken" << std::endl;
		map.breakLink();
		reload();
	}

};

REGISTER_COMPONENT(container::Simple_component_factory<netcontrol>, netcontrol);
