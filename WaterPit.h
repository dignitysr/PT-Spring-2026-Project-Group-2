#pragma once
#include "GameObject.h"
class WaterPit:public GameObject
{
public:
	WaterPit(const CellPosition & waterPitPosition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a water pit in the cell

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the water pit

	void WaterPit::Save(ofstream& OutFile, GameObjectType type);
	bool IsType(GameObjectType type) const;
	void WaterPit::Load(ifstream& InFile);
	WaterPit* Clone() const; // Creates and returns a pointer to a new copy of the WaterPit (used in copy/cut/paste)
	virtual ~WaterPit();
};

