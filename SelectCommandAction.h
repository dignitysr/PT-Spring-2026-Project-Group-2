#pragma once

#include "Action.h"
#include "DEFS.h"
#include "UI_Info.h"

class SelectCommandAction : public Action
{

public:
	SelectCommandAction(ApplicationManager* pApp);

	virtual bool ReadActionParameters();
	virtual void Execute();

	virtual ~SelectCommandAction();
};