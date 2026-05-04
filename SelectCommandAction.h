#pragma once

#include "Action.h"
#include "DEFS.h"
#include "UI_Info.h"

class SelectCommandAction : public Action
{
	Command availableCommands[MaxAvailableCommands];
	int availableCommandsCount;

public:
	SelectCommandAction(ApplicationManager* pApp);

	virtual bool ReadActionParameters();
	virtual void Execute();

	virtual ~SelectCommandAction();
};