#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Workshop.h"  

class AddWorkshopAction : public Action
{
private:
    CellPosition pos; // The position of the workshop

public:
    AddWorkshopAction(ApplicationManager* pApp); // Constructor
    virtual bool ReadActionParameters(); // Reads and checks the selected position
    virtual void Execute(); // Creates a new workshop object and adds it to the grid
    virtual ~AddWorkshopAction(); // Destructor
};