#include <network.hh>

#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_array.hpp>
#include <netinet/in.h>
#include "assert.hh"
#include "component.hh"
//#include "packet-in.hh"
#include "ofp-msg-event.hh"
#include "datapath-join.hh"
#include "vlog.hh"
#include "flowmod.hh"

#include "netinet++/ethernet.hh"

#include "../../../oflib/ofl-structs.h"
#include "../../../oflib/ofl-messages.h"


using namespace vigil;
using namespace vigil::container;

class Afdx : public Component {
        Network network;
        Network topology() {
                std::vector<Host> hosts;
                hosts.push_back(Host());
                hosts.push_back(Host());
                return Network(VLSet(), hosts);
        }

        VL vl1() {
                std::vector<Switch> swts;
                swts.push_back(Switch());
                return VL(1, 1, 0, SLA(), swts, this);
        }

        VL vl2() {
                std::vector<Switch> swts;
                swts.push_back(Switch());
                return VL(2, 0, 1, SLA(), swts, this);
        }
public:
        Afdx(const Context* c, const json_object*) : Component(c), network(topology())
        {}

        void configure(const Configuration*) {
        }

        void install() {
                // Здесь будет запуск функций
                std::cout << "/* message */" << '\n';
                register_handler(Datapath_join_event::static_get_name(), boost::bind(&Afdx::handler, this, _1));
        }

        Disposition handler (const Event& e) {
                network.addVL(vl1());
                network.addVL(vl2());
                return STOP;
        }
};

REGISTER_COMPONENT(container::Simple_component_factory<Afdx>, Afdx);
