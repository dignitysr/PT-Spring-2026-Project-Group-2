#pragma once
#include "DEFS.h"
#include "Grid.h"

// Forward declarations
class Player;
class GameState;

// Base class for all game objects (Belt, Flag, WaterPit, DangerZone, RotatingGear, Workshop, Antenna).
class GameObject
{
protected:

	CellPosition position; // The cell this object occupies

public:

	GameObject(const CellPosition& pos);

	CellPosition GetPosition() const;

	virtual void SetPosition(const CellPosition pos, Grid* pGrid);

	// ============ Virtual Functions ============

	virtual void Draw(Output* pOut) const = 0;

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer) = 0;

	// Abdallah edited this part
	// Save / Load (uncomment and implement in derived classes when needed)
	//pure virtual:every object defines how to write itself to a file(overriding fns)
	virtual void Save(ofstream& OutFile,GameObjectType type) = 0;

	virtual void Load(ifstream& Infile)  = 0;
	//end of editing

	virtual bool IsType(GameObjectType type) const = 0; // Checks if the object is of the passed type (e.g. FLAG_TYPE) and returns true if it is, otherwise returns false

	virtual GameObject* Clone() const = 0; // Creates and returns a pointer to a new copy of the GameObject (used in copy/cut/paste)

	virtual ~GameObject();
};
