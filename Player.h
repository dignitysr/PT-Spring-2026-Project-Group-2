#pragma once

#include "Grid.h"
#include "Cell.h"

#define MaxHealth 10

// Forward declaration: GameState is needed for Move() but we don't include it
// here to avoid a circular dependency (GameState.h includes Player.h).
class GameState;

class Player
{
	Cell* pCell;           // Pointer to the cell the player currently occupies
	const int playerNum;   // Player index 0..MaxPlayerCount-1 (constant after construction)

	Direction currDirection; // The direction the player is currently facing
	int health;              // Player's current health points

	// ---- Saved Commands (the player's "program" for this round) ----
	// Owned here because they are player-specific state.
	// SelectCommandAction fills this array; Move() executes it; ClearSavedCommands() resets it.
	Command savedCommands[MaxSavedCommandsWithExtendedMemory];
	int savedCommandCount; // how many commands have been saved so far 
	bool extendedMemory = false;

	Command availableCommands[MaxAvailableCommands]; // the commands available to the player this round (depends on health)
	int availabeCommandCount = MaxAvailableCommands; // how many commands are available this round (0..MaxAvailableCommands)

	// ---- [OPTIONAL BONUS] Shooting Phase data members ----
	// Uncomment when adding the shooting phase (see DEFS.h PhaseType):
	int laserDamage; // damage per shot (default = 1; double-laser consumable = 2)
	bool isHacked;   // true = this player skips their turn this round

	// ---- [OPTIONAL BONUS] Workshop Consumables data members ----
	// Uncomment when adding consumables (see Workshop.h):
	//   Consumable* inventory[MaxConsumables];
	//   int inventoryCount;
	bool hasToolkit = false;
	bool hasHackDevice = false;

public:

	Player(Cell* pCell, int playerNum); // Initialises all data members

	// ====== Setters and Getters ======

	void  SetCell(Cell* cell);
	Cell* GetCell() const;

	void SetHealth(int h);
	int  GetHealth() const;

	Direction GetDirection() const;
	void      SetDirection(Direction d);

	///TODO: Add more setters/getters here as needed

	int GetPlayerNum() const; // Returns the player number (0..MaxPlayerCount-1)
	void ActivateExtendedMemory() { extendedMemory = true; }
	bool HasExtendedMemory() const { return extendedMemory; }
	int GetMaxCommands() const { return extendedMemory ? MaxSavedCommandsWithExtendedMemory : MaxSavedCommands; }

	void AddToolkit();
	void AddHackDevice();

	bool HasToolkit() const;
	bool HasHackDevice() const;

	void UseToolkit();
	void UseHackDevice();

	void SetHacked(bool value);
	bool IsHacked() const;
	// ====== Saved Commands ======

	void    AddSavedCommand(Command cmd);         // Appends cmd to savedCommands (called by SelectCommandAction)
	void    ClearSavedCommands();                 // Resets the saved-command list (call at the start of each round)
	int     GetSavedCommandCount() const;
	Command GetSavedCommand(int index) const;

	Command GetAvailableCommand(int index) const; // Returns the available command at the given index (called by SelectCommandAction)
	int    GetAvailableCommandCount() const;    // Returns the number of available commands (called by SelectCommandAction)

	void RandomizeAvailableCommands(); // Fills availableCommands based on current health (called by gamestate)

	// ====== Drawing ======

	void Draw(Output* pOut) const;         // Draws the player token on its current cell
	void DrawCommands(Output* pOut);      // Draws the player's saved commands in the commands bar (since they're all here i thought it was appropriate)
	void ClearDrawing(Output* pOut) const; // Erases the player token (restores cell colour)

	// ====== Game Logic ======

	void ExecuteCommand(Command cmd, Grid* pGrid, GameState* pState); // Helper function for Move()
	void Move(Grid* pGrid, GameState* pState);

	void AppendPlayerInfo(string& playersInfo) const; // Appends "P0(direction, health)" to the string
};
