#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "DangerZone.h"  

class AddDangerZoneAction : public Action
{
private:
    CellPosition pos;  

public:
    AddDangerZoneAction(ApplicationManager* pApp);  
    virtual bool ReadActionParameters();        
    virtual void Execute();                     
    virtual ~AddDangerZoneAction();               
};