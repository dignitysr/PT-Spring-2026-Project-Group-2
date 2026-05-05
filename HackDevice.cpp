#include "HackDevice.h"
#include "Player.h"

ConsumableType HackDevice::GetType() const
{
	return HACK_DEVICE;
}

void HackDevice::ApplyEffect(Player* pPlayer, GameState* pState)
{
	pPlayer->SetHacked(true);
}