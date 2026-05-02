#pragma once

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Player.h" 

class RebootRepairAction : public Action
{
public:
    RebootRepairAction(ApplicationManager* pApp); 
    virtual void ReadActionParameters();           
    virtual void Execute();                        
    virtual ~RebootRepairAction();                 
};