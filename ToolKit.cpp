#include "ToolKit.h"
#include "Player.h"

ConsumableType ToolKit::GetType() const
{
	return TOOLKIT;
}

void ToolKit::ApplyEffect(Player* pPlayer, GameState* pState)
{
	pPlayer->SetHealth(MaxHealth);
}