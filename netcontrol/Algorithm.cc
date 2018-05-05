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
		// TODO: log base failed
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
		// TODO: log base failed
		const VLSet vls = additionalStep();
		return vls;
	}
}

VLSet Algorithm::baseStep()
{
}

VLSet Algorithm::additionalStep()
{
}
