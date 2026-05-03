#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Cell.h"
class CutObjectAction :public Action
{
	Cell* cellToCut;
public:

	CutObjectAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters(); // Reads action parameters 

	virtual void Execute(); // copies object to clipboard

	~CutObjectAction();
};

