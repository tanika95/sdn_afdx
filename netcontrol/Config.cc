#include "Config.hh"

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
	read_xml(file, tree);
}

Topology Config::topology()
{
}

VLSet Config::dataflows()
{
	VLSet vls;
	BOOST_FOREACH(ptree::value_type &vl, tree.get_child("links")) {
        	uint32_t id = vl.second.get<uint32_t>("vl.id");
		uint32_t sender = vl.second.get<uint32_t>("vl.sender");
		uint32_t reciever = vl.second.get<uint32_t>("vl.reciever");
		double bag = vl.second.get<uint32_t>("vl.bag");
		double lmax = vl.second.get<uint32_t>("vl.lmax");
		double jitt = vl.second.get<uint32_t>("vl.jitter");
		vls.push_back(VL(id, sender, reciever, SLA(bag, lmax, jitt)));
	}
	return vls;
}
