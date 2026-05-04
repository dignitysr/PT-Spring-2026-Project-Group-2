#include "DoubleLaser.h"
#include "Player.h"

ConsumableType DoubleLaser::GetType() const
{
	return DOUBLE_LASER;
}

void DoubleLaser::ApplyEffect(Player* pPlayer, GameState* pState)
{
	pPlayer->SetLaserDamage(2); // Set laser damage to 2 for this player
}

void DoubleLaser::DisengageEffect(Player* pPlayer, GameState* pState)
{
	pPlayer->SetLaserDamage(1); // Reset laser damage to default (1) for this player
}