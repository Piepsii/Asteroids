#pragma once
#include "Command.h"
class RotateShipCommand :
    public Command
{
public:
    virtual void execute(Ship& _ship, float _param);
};

