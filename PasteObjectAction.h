#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Cell.h"
class PasteObjectAction :public Action
{
	Cell* cellToPaste;
public:

	PasteObjectAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters(); // Reads action parameters 

	virtual void Execute(); // copies object to clipboard

	~PasteObjectAction();
};

