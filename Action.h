#pragma once

#include "ApplicationManager.h"
#include "Cell.h"

// Base class for all possible actions (actions are icons of the toolbar)
class Action
{
protected:

	ApplicationManager *pManager;	// Actions needs ApplicationManager to do their job

public:

	Action(ApplicationManager *pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual bool ReadActionParameters() = 0; // Reads parameters required for action to execute 
	                                         // (code depends on action type so virtual)
											 // changed to bool so that it can return false if parameters are invalid and hence prevent execution of the action

	virtual void Execute() = 0;  // Executes action (code depends on action type so virtual)

	virtual ~Action();  // Virtual Destructor
};

