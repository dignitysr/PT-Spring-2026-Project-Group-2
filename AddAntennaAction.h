#pragma once

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Antenna.h"

class AddAntennaAction : public Action
{
private:
    // antenna cell position
    CellPosition pos;

public:
    // constructor
    AddAntennaAction(ApplicationManager* pApp);
    // reads and checks the selected position
    virtual bool ReadActionParameters();
    // adds the antenna to the grid
    virtual void Execute();
    // destructor
    virtual ~AddAntennaAction();
};