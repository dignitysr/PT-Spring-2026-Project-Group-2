#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Antenna.h"  

class AddAntennaAction : public Action
{
private:
    CellPosition pos;  

public:
    AddAntennaAction(ApplicationManager* pApp);  
    virtual void ReadActionParameters();         
    virtual void Execute();                      
    virtual ~AddAntennaAction();                 
};