#include "TeleportShipCommand.h"

void TeleportShipCommand::execute(Ship& _ship, float _param)
{
	_ship.teleport();
}
