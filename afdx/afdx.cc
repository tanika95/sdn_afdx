#include <network.hh>


#include <boost/bind.hpp>
#include <unistd.h>
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
                hosts.push_back(Host());
                return Network(VLSet(), hosts, 3);
        }

        VL vl1() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 1, 1, 2));
                swts.push_back(Switch(jitt, 2, 2, 3));
                swts.push_back(Switch(jitt, 3, 3, 1));
                return VL(1, 1, 0, SLA(1, 800), swts, this);
        }

        VL vl2() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 2, 1, 3));
                swts.push_back(Switch(jitt, 3, 3, 2));
                swts.push_back(Switch(jitt, 1, 3, 1));
                return VL(2, 1, 0, SLA(1, 1200), swts, this);
        }

        VL vl3() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 3, 1, 2));
                swts.push_back(Switch(jitt, 1, 3, 2));
                swts.push_back(Switch(jitt, 2, 2, 1));
                return VL(3, 1, 0, SLA(1, 700), swts, this);
        }

        VL vl4() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 1, 1, 2));
                swts.push_back(Switch(jitt, 2, 2, 1));
                return VL(4, 1, 0, SLA(1, 600), swts, this);
        }

        VL vl5() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 3, 1, 2));
                swts.push_back(Switch(jitt, 1, 3, 1));
                return VL(5, 1, 0, SLA(1, 1100), swts, this);
        }

        VL vl6() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 2, 1, 3));
                swts.push_back(Switch(jitt, 3, 3, 1));
                return VL(6, 1, 0, SLA(1, 1000), swts, this);
        }

        VL vl1new() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 1, 1, 3));
                swts.push_back(Switch(jitt, 3, 2, 1));
                return VL(1, 1, 0, SLA(1, 800), swts, this);
        }

        VL vl3new() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 3, 1, 3));
                swts.push_back(Switch(jitt, 2, 3, 1));
                return VL(3, 1, 0, SLA(1, 1200), swts, this);
        }

        VL vl4new() {
                std::vector<Switch> swts;
                double jitt = 0.1;
                swts.push_back(Switch(jitt, 1, 1, 3));
                swts.push_back(Switch(jitt, 3, 2, 3));
                swts.push_back(Switch(jitt, 2, 3, 1));
                return VL(4, 1, 0, SLA(1, 700), swts, this);
        }

        void scenario() {
                std::cout << "LOG: Starting scenario 3.B-D" << std::endl;
                VL vl_1 = vl1();
                VL vl_3 = vl3();
                VL vl_4 = vl4();
                network.addVL(vl_1);
                network.addVL(vl2());
                network.addVL(vl_3);
                network.addVL(vl_4);
                network.addVL(vl5());
                network.addVL(vl6());
                char now;
                std::cin >> now;
                std::cout << "LOG: s1-s2 break" << std::endl;
                network.removeVL(vl_4);
                network.addVL(vl4new());
                network.removeVL(vl_1);
                network.addVL(vl1new());
                network.removeVL(vl_3);
                network.addVL(vl3new());
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
                scenario();
                return STOP;
        }
};

REGISTER_COMPONENT(container::Simple_component_factory<Afdx>, Afdx);
