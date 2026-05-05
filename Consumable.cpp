#include "Consumable.h"
#include "Player.h"

void Consumable::DisengageEffect(Player* pPlayer, GameState* pState)
{
	// By default, consumables have no disengage effect, but you can override this in derived classes if needed.
}

Consumable::~Consumable()
{
	
}