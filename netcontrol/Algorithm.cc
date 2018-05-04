#include "Algorithm.hh"

VlSet Algorithm::run()
{
	try {
		const auto vls = baseStep();
		return vls;
	} catch(const exception &e) {
		// TODO: log base failed
		const auto vls = additionalStep();
		return vls;
	}
}

VlSet Algorithm::initial()
{
	try {
		const auto vls = baseStep();
		return vls;
	} catch(const exception &e) {
		// TODO: log base failed
		const auto vls = additionalStep();
		return vls;
	}
}

void Algorithm::baseStep()
{
}

void Algorithm::additionalStep()
{
}
