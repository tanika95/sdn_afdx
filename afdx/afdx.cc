#include <network.hh>


#include <boost/bind.hpp>
#include "datapath-join.hh"

using namespace vigil;
using namespace vigil::container;

class Afdx : public Component {
        Network network;
        uint32_t switches_num;
        Network topology() {
                std::vector<Host> hosts;
                hosts.push_back(Host());
                hosts.push_back(Host());
                return Network(VLSet(), hosts, 1);
        }

        VL vl1() {
                std::vector<Switch> swts;
                swts.push_back(Switch(0, 1));
                return VL(1, 1, 0, SLA(1, 10), swts, this);
        }

        VL vl2() {
                std::vector<Switch> swts;
                swts.push_back(Switch(Switch(0, 1)));
                return VL(2, 0, 1, SLA(1, 10), swts, this);
        }
public:
        Afdx(const Context* c, const json_object*)
                : Component(c), network(topology()), switches_num(0)
        {}

        void configure(const Configuration*) {
        }

        void install() {
                register_handler(Datapath_join_event::static_get_name(), boost::bind(&Afdx::handler, this, _1));
        }

        Disposition handler (const Event& e) {
                switches_num++;
                if (switches_num != network.switchesAmount()) {
                        return CONTINUE;
                }
                // Все коммутаторы подключились - можно прокладывать ВК
                VL vl = vl1();
                network.addVL(vl);
                network.addVL(vl2());
                network.removeVL(vl);
                return STOP;
        }
};

REGISTER_COMPONENT(container::Simple_component_factory<Afdx>, Afdx);
