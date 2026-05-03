#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "WaterPit.h" 

class AddWaterPitAction : public Action
{
private:
    CellPosition pos;  

public:
    AddWaterPitAction(ApplicationManager* pApp);  
    virtual bool ReadActionParameters();          
    virtual void Execute();                       
    virtual ~AddWaterPitAction();                
};