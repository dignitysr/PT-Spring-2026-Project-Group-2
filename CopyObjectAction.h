#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Cell.h"
class CopyObjectAction :public Action
{
	Cell* cellToCopy;
public:

	CopyObjectAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads action parameters 

	virtual void Execute(); // copies object to clipboard

	~CopyObjectAction();
};

