#include <vector>
#include "vl.hh"


class Host {
	bool alive;
	std::vector<int> out_vl_ids;
	std::vector<int> in_vl_ids;
public:
	std::vector<int> incomingVlIds();
	std::vector<int> outcomingVlIds();
	void addIncoming(const VL &vl);
	void addOutcoming(const VL &vl);
	void removeIncoming(const VL &vl);
	void removeOutcoming(const VL &vl);
	void die();
};

class Network {
public:
	Network(const VLSet &vls, const std::vector<Host> &hsts);
	
	void addVL(const VL &vl);
	void addVLs(const std::vector<VL> &vls);
	void removeVL(const VL &vl);
	void removeVLs(const std::vector<VL> &vls);
	void removeHost(int id);
	Host host(int id);
private:
	VLSet vls;
	std::vector<Host> hosts;
};
