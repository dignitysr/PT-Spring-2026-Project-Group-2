#pragma once

#include "Action.h"

class ExecuteCommandsAction : public Action
{
public:
	ExecuteCommandsAction(ApplicationManager* pApp); // Constructor

	virtual bool ReadActionParameters(); // Checks if the current player has saved commands
	virtual void Execute(); // Executes the saved commands for the current player

	virtual ~ExecuteCommandsAction(); // Destructor
};