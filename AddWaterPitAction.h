#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "WaterPit.h" 

class AddWaterPitAction : public Action
{
private:
    CellPosition pos; // The position of the water pit

public:
    AddWaterPitAction(ApplicationManager* pApp); // Constructor
    virtual bool ReadActionParameters(); // Reads and checks the selected position
    virtual void Execute(); // Creates a new water pit object and adds it to the grid
    virtual ~AddWaterPitAction(); // Destructor
};