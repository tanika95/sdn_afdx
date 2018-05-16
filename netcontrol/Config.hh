#pragma once

#include <string>
#include <boost/property_tree/ptree.hpp>

#include "Topology.hh"
#include "Vl.hh"

class Config
{
public:
	Config(const std::string &file);
	Topology topology();
	VLSet dataflows();
private:
	boost::property_tree::ptree tree;
};
