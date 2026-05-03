#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Output.h"


class RotatingGear : public GameObject
{
	bool isClockWise; // if it is true then direction is clockwise, if it is false then direction is anticlockwise
public:
	RotatingGear(const CellPosition & gearposition,bool clockwise); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a rotating gear in a selected cell
	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the rotating gear
	bool GetisClockWise() const; // Getter for the direction
	void RotatingGear::Save(ofstream& OutFile, GameObjectType type);
	bool IsType(GameObjectType type) const;
	void RotatingGear::Load(ifstream& InFile);
	RotatingGear* Clone() const; // Creates and returns a pointer to a new copy of the RotatingGear (used in copy/cut/paste)
	virtual ~RotatingGear();
};

