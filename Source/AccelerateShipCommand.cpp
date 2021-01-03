#include "AccelerateShipCommand.h"

void AccelerateShipCommand::execute(Ship& _ship, float _param)
{
	_ship.accelerate(_param);
}
