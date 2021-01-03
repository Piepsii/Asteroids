#pragma once
#include "Command.h"
class AccelerateShipCommand :
    public Command
{
public:
    void execute(Ship& _ship, float _param);
};

