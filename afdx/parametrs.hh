class Switch {
	int id; // возможно лишнее поле
	int jitter;
public:
	int jswitch();
};

class SLA {
	int max_packet_length;
	int bandwidth_allocation_gap;
public:
	int bag();
	int lmax();
};
