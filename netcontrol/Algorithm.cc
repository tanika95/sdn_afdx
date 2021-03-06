#include "Algorithm.hh"

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

using namespace std;
using namespace boost;

bool vlbwsort (VL vl1, VL vl2) { return vl1.bw() > vl2.bw(); }
bool vlidsort (VL vl1, VL vl2) { return vl1.id() < vl2.id(); }

Algorithm::Algorithm(VLSet vls, Topology topo)
	: links(vls), map(topo)
{}

VLSet Algorithm::run()
{
	try {
		const VLSet vls = baseStep();
		return vls;
	} catch(const std::exception &e) {
		cout << "LOG: Base step has failed" << endl;
		const VLSet vls = additionalStep();
		return vls;
	}
}

VLSet Algorithm::initial()
{
	cout << "LOG: Starting initial configuring" << endl;
	sort(links.begin(), links.end(), vlbwsort);
	for (uint32_t i = 0; i < links.size(); i++) {
		links[i] = searchPath(links[i], links[i].sender(), links[i].receiver());
	}
	sort(links.begin(), links.end(), vlidsort);
	return links;
}

VLSet Algorithm::baseStep()
{
	cout << "LOG: Starting base step" << endl;
	sort(links.begin(), links.end(), vlbwsort);
	for (uint32_t i = 0; i < links.size(); i++) {
		State state = map.stateForVL(links[i]);
		if (state.broken) {
			links[i] = searchPath(links[i], state.v1, state.v2);
		}
	}
	sort(links.begin(), links.end(), vlidsort);
	return links;
}

VLSet Algorithm::additionalStep()
{
	cout << "LOG: Starting base step" << endl;
	sort(links.begin(), links.end(), vlbwsort);
	bool add_set = false;
	for (uint32_t i = 0; i < links.size(); i++) {
		State state = map.stateForVL(links[i]);
		if (state.broken || add_set) {
			links[i] = searchPath(links[i], state.v1, state.v2);
			add_set = true;
		}
	}
	sort(links.begin(), links.end(), vlidsort);
	return links;
}

VL Algorithm::searchPath(const VL &vl, uint32_t from, uint32_t to)
{
	Graph network = map.graphForVL(vl);
	vector<Vertex> path(num_vertices(network), graph_traits<Graph>::null_vertex());
	Vertex start = vertex(from, network);
	vector<double> distances(num_vertices(network));

	dijkstra_shortest_paths(network, start,
		predecessor_map(&path[0]).distance_map(&distance[0]));
	IndexMap index = get(vertex_index, network);

	Route route;
	int v = to;
	if (d[to] == 0) {
		throw runtime_error("Путь не найден");
	}
	while (path[v] != v) {
		int prev = v;
		v = path[v];
		map.decreaseBw(vl.bw(), v, prev);
		if (path[v] == v) {
			break;
		}
		route.push_back(Switch(index[v], map.port(index[v], index[path[v]]),
			map.port(index[v], index[prev])));
	}
	return VL(vl, route);
}

Topology Algorithm::updateTopo()
{
	map.reloaded();
	return map;
}
