#pragma once
#include "DEFS.h"
#include "ApplicationManager.h"

class Player;

class Consumable
{
	protected:
		ConsumableType type; // The type of the consumable
	public:
		virtual ConsumableType GetType() const = 0; // Returns the type of the consumable
		virtual void ApplyEffect(Player* pPlayer, GameState* pState) = 0; // Applies the effect of the consumable to the player (e.g. increases health, adds a command, etc.)
		virtual void DisengageEffect(Player* pPlayer, GameState* pState);
		virtual ~Consumable();
};

