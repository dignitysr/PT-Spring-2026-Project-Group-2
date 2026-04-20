#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode
	SET_FLAG_CELL,	// Set Flag on a Cell
	EXIT,			// Exit Application
	TO_PLAY_MODE,	// Go to Play Mode

	///TODO: Add more action types of Design Mode
	ADD_ANTENNA,
	ADD_BELT,
	ADD_WATER_PIT,
	ADD_DANGER_ZONE,
	ADD_WORKSHOP,
	ADD_ROTATING_GEAR_CLOCKWISE,
	ADD_ROTATING_GEAR_ANTICLOCKWISE,
	COPY_OBJECT,
	CUT_OBJECT,
	PASTE_OBJECT,
	DELETE_OBJECT,
	SAVE_GRID,
	LOAD_GRID,

	//  [2] Actions of Play Mode

	EXECUTE_COMMANDS,	// Execute the saved commands
	SELECT_COMMAND,		// Select a command from the available ones to be executed
	REBOOT_REPAIR,    // added this
	NEW_GAME,         //added this
	TO_DESIGN_MODE,	// Go to Design Mode

	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,							// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,						// Inside Grid Area
	COMMAND,						// Inside Command Bar Area
	STATUS 							// Inside StatusBar Area
};

enum Direction // Directions of the game
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum PhaseType
{
	PHASE_MOVEMENT,  // players execute their saved commands

	///TODO: Add more phases here as needed
};

enum Command
{
	NO_COMMAND,
	MOVE_FORWARD_ONE_STEP,
	MOVE_BACKWARD_ONE_STEP,
	MOVE_FORWARD_TWO_STEPS,
	MOVE_BACKWARD_TWO_STEPS,
	MOVE_FORWARD_THREE_STEPS,
	MOVE_BACKWARD_THREE_STEPS,
	ROTATE_CLOCKWISE,
	ROTATE_COUNTERCLOCKWISE,

	COMMANDS_COUNT,
};

const int MaxSavedCommands = 5;

enum CommandType
{
	AVAILABLE,
	SAVED,
};

#endif