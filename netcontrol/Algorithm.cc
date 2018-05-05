#include "Algorithm.hh"

using namespace std;

Algorithm::Algorithm(VLSet vls, Topology topo)
	: links(vls), map(topo)
{}

VLSet Algorithm::run()
{
	try {
		const VLSet vls = baseStep();
		return vls;
	} catch(const exception &e) {
		cout << "LOG: Base step has failed" << endl;
		const VLSet vls = additionalStep();
		return vls;
	}
}

VLSet Algorithm::initial()
{
	try {
		const VLSet vls = baseStep();
		return vls;
	} catch(const exception &e) {
		cout << "LOG: Base step has failed" << endl;
		const VLSet vls = additionalStep();
		return vls;
	}
}

VLSet Algorithm::baseStep()
{
	cout << "LOG: Starting base step" << endl;
}

VLSet Algorithm::additionalStep()
{
	cout << "LOG: Starting additional step" << endl;
}
