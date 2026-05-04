#pragma once

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Player.h" 

class RebootRepairAction : public Action
{
public:
    RebootRepairAction(ApplicationManager* pApp); // Constructor
    virtual bool ReadActionParameters(); // Reads repair action parameters
    virtual void Execute(); // Repairs the current player's robot
    virtual ~RebootRepairAction(); // Destructor
};