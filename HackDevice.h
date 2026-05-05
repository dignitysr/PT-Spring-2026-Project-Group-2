#pragma once
#include "Consumable.h"
class HackDevice :
    public Consumable
{
public:
    virtual ConsumableType GetType() const; // Returns the type of the consumable
    virtual void ApplyEffect(Player* pPlayer, GameState* pState); // Applies the effect of the consumable to the player (e.g. increases health, adds a command, etc.)
};

