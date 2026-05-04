#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "DangerZone.h"  

class AddDangerZoneAction : public Action
{
private:
    CellPosition pos; // The position of the danger zone

public:
    AddDangerZoneAction(ApplicationManager* pApp); // Constructor
    virtual bool ReadActionParameters(); // Reads and checks the selected position
    virtual void Execute(); // Creates a new danger zone object and adds it to the grid
    virtual ~AddDangerZoneAction(); // Destructor
};