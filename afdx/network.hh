#include <vector>
#include "vl.hh"


class Host {
	bool alive;
	std::vector<uint32_t> out_vl_ids;
	std::vector<uint32_t> in_vl_ids;
public:
	std::vector<uint32_t> incomingVlIds();
	std::vector<uint32_t> outcomingVlIds();
	void addIncoming(const VL &vl);
	void addOutcoming(const VL &vl);
	void removeIncoming(const VL &vl);
	void removeOutcoming(const VL &vl);
	void die();
};

class Network {
public:
	Network(const VLSet &vls, const std::vector<Host> &hsts, uint32_t amount);

	void addVL(const VL &vl);
	void addVLs(const std::vector<VL> &vls);
	void removeVL(const VL &vl);
	void removeVLs(const std::vector<VL> &vls);
	void removeHost(uint32_t id);
	Host host(uint32_t id);
	uint32_t switchesAmount();
private:
	VLSet vls;
	std::vector<Host> hosts;
	uint32_t switches_amount;
};
