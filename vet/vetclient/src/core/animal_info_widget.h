#pragma once

#include "types/animalstate.h"

class AnimalInfoWidget
{
public:
	AnimalInfoWidget();
	void show();

private:
	AnimalState state;
};

