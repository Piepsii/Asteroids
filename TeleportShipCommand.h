#pragma once
#include "Command.h"
class TeleportShipCommand :
    public Command
{
    void execute(Ship& _ship, float _param);
};

