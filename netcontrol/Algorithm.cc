#include "Algorithm.hh"

using namespace std;

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
