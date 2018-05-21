#pragma once

#include <map>
#include <utility>
#include <stdint.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "Host.hh"
#include "Vl.hh"
#include "Link.hh"

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
	boost::no_property, boost::property<boost::edge_weight_t, double> > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::pair<int, int> Edge;

class State {
public:
	State(bool br, uint32_t s1, uint32_t s2) {
		broken = br;
		v1 = s1;
		v2 = s2;
	};
	bool broken;
	uint32_t v1;
	uint32_t v2;
};

class Topology
{
public:
	Topology(std::map<uint32_t, Host> hst, uint32_t switches, Links lnks);

	Graph graphForVL(const VL &vl) const;
	State stateForVL(const VL &vl) const;
	uint32_t switchesAmount() const;
	uint32_t port(uint32_t from, uint32_t to);

	void breakLink(uint32_t s1, uint32_t s2);
	void breakComm(uint32_t s1);
	void breakHost(uint32_t id);
	void decreaseBw(double bw, uint32_t from, uint32_t to);

	void addVlToHost(const VL &vl);
	void removeVlFromHost(const VL &vl);
	void reloaded();
private:
	std::map<uint32_t, Host> hosts;
	uint32_t swtch_num;
	Links links;
	Links broken;
};
