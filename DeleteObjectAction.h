#pragma once
#include "Action.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Cell.h"
class DeleteObjectAction :public Action
{
private:
	Cell* celltodelete;
public:
    DeleteObjectAction(ApplicationManager* pApp);
    virtual bool ReadActionParameters();
    virtual void Execute();
    ~DeleteObjectAction();
};
