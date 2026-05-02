#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Workshop.h"  

class AddWorkshopAction : public Action
{
private:
    CellPosition pos;  

public:
    AddWorkshopAction(ApplicationManager* pApp);  
    virtual void ReadActionParameters();         
    virtual void Execute();                  
    virtual ~AddWorkshopAction();              
};