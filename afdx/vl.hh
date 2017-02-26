#include <map>
#include <vector>
#include "parametrs.hh"
#include "component.hh"

using namespace vigil;
using namespace vigil::container;

class VL {
public:
	VL(int vl_id, int s_id, int r_id, SLA prms, std::vector<Switch> swts, Component *c);
	VL();

	void add() const;
	void remove() const;
	SLA sla() const;
	int id() const;
	int sender() const;
	int receiver() const;
private:
	int vl_id;
	int sender_id;
	int receiver_id;
	SLA params;
	std::vector<Switch> switches;
	Component *app;
};

class VLSet {
public:
	void add(const VL &vl);
	void remove(int id);
	VL vl(int id);
private:
	std::map<int, VL> vls;
};
