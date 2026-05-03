#pragma once
#include "GameObject.h"
class Flag :public GameObject
{
public:
	Flag(const CellPosition & flagposition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a flag in a selected cell
	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the flag
	void Flag::Save(ofstream& OutFile, GameObjectType type);
	bool IsType(GameObjectType type) const;
	void Flag::Load(ifstream& InFile);
	Flag* Clone() const; // Creates and returns a pointer to a new copy of the Flag (used in copy/cut/paste)
	virtual ~Flag(); // Virtual destructor
};