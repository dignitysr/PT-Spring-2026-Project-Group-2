#pragma once

#include "Action.h"
#include "DEFS.h"
#include "UI_Info.h"

// Action class responsible for selecting commands from available options.
class SelectCommandAction : public Action
{
public:
	// Constructor to initialize the action with ApplicationManager pointer.
	SelectCommandAction(ApplicationManager* pApp);
	// Reads the parameters required for selecting commands.
	virtual bool ReadActionParameters();
	// Executes the action by allowing the player to select commands.
	virtual void Execute();
	// Destructor for cleanup.
	virtual ~SelectCommandAction();
};