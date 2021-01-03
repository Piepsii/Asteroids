#pragma once
#include "Ship.h"

class Command
{
public:
	virtual ~Command();
	virtual void execute(Ship &_ship, float _param) = 0;
};

