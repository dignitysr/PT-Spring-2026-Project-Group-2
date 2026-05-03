#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Output.h"


// Workshop: a special cell that applies an effect on the player who lands on it.
// [OPTIONAL BONUS] Consumables can be added as an extension.
class Workshop : public GameObject
{
public:
	Workshop(const CellPosition & workshopPosition);
	virtual void Draw(Output* pOut) const; // Draws workshop

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the workshop

	void Workshop::Save(ofstream& OutFile, GameObjectType type);
	bool IsType(GameObjectType type) const;
	void Workshop::Load(ifstream& InFile);
	Workshop* Clone() const; // Creates and returns a pointer to a new copy of the Workshop (used in copy/cut/paste)
	~Workshop();
};

