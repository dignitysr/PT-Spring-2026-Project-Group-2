#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

//I added this part(Abdallah) to intialize the Desing Mode Items
enum DesignMenuItem {
	ITM_SET_FLAG_CELL,
	ITM_EXIT,			
	ITM_TO_PLAY_MODE,	

	ITM_ADD_ANTENNA,
	ITM_ADD_BELT,
	ITM_ADD_WATER_PIT,
	ITM_ADD_DANGER_ZONE,
	ITM_ADD_WORKSHOP,
	ITM_ADD_ROTATING_GEAR,
	ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_DELETE,
	ITM_SAVE,
	ITM_LOAD,
};
//End of addition
//I added this part(Abdallah) to intialize the Play Mode Items
enum PlayMenuItem {
	ITM_SELECT_COMMAND,
	ITM_EXECUTE_COMMANDS,
	ITM_SWITCH_TO_DESIGN_MODE,
	ITM_REBOOT_REPAIR,
	ITM_NEW_GAME,
	ITM_EXIT_PLAY,
};
//End of addition

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
	ADD_ROTATING_GEAR,
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
	STATUS 							// Inside StatusBar Area
};

enum Direction // Directions of the game
{
	UP,
	DOWN,
	RIGHT,
	LEFT
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

#endif