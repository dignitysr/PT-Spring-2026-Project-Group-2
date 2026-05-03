#pragma once
#include "GameObject.h"
class DangerZone:public GameObject
{
public:
	DangerZone(const CellPosition & dangerZonePosition);
	virtual void Draw(Output* pOut) const; // Draws a danger zone in the cell

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the danger zone

	void DangerZone::Save(ofstream& OutFile, GameObjectType type);
	bool IsType(GameObjectType type) const;
	void DangerZone::Load(ifstream& InFile);
	DangerZone* Clone() const; // Creates and returns a pointer to a new copy of the DangerZone (used in copy/cut/paste)
	virtual ~DangerZone();
};

