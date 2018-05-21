#include "Config.hh"

#include <algorithm>
#include <vector>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Sla.hh"
#include "Vl.hh"

using namespace std;
using namespace boost::property_tree;


Config::Config(const string &file)
{
	std::cout << "LOG: Open config" << std::endl;
	read_xml(file, tree);
}

Topology Config::topology()
{
	std::map<uint32_t, Host> hosts;
	BOOST_FOREACH(ptree::value_type &h, tree.get_child("map.hosts")) {
        	uint32_t id = h.second.get<uint32_t>("");
		hosts[id] = Host();
	}
        uint32_t swtch_num = tree.get<uint32_t>("map.switches");

	Links links;
	BOOST_FOREACH(ptree::value_type &l, tree.get_child("map.links")) {
        	uint32_t v1 = l.second.get<uint32_t>("v1");
		uint32_t v2 = l.second.get<uint32_t>("v2");
		uint32_t p1 = l.second.get<uint32_t>("port1");
		uint32_t p2 = l.second.get<uint32_t>("port2");
		double bw = l.second.get<uint32_t>("bw");
		links[make_pair(v1, v2)] = Link(v1, v2, p1, p2, bw);
		links[make_pair(v2, v1)] = Link(v2, v1, p2, p1, bw);
	}
	return Topology(hosts, swtch_num, links);
}

VLSet Config::dataflows()
{
	VLSet vls;
	BOOST_FOREACH(ptree::value_type &vl, tree.get_child("links")) {
        	uint32_t id = vl.second.get<uint32_t>("id");
		uint32_t sender = vl.second.get<uint32_t>("sender");
		uint32_t reciever = vl.second.get<uint32_t>("reciever");
		double bag = vl.second.get<uint32_t>("bag");
		double lmax = vl.second.get<uint32_t>("lmax");
		double jitt = vl.second.get<double>("jitter");
		vls.push_back(VL(id, sender, reciever, SLA(bag, lmax, jitt)));
	}
	return vls;
}
