#include "RotateShipCommand.h"

void RotateShipCommand::execute(Ship& _ship, float _param)
{
	_ship.rotate(_param);
}
