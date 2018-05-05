#pragma once
#include "Vlset.hh"

class Algorithm
{
public:
	VLSet run();
	VLSet initial();
private:
	VLSet baseStep();
	VLSet additionalStep();
};
