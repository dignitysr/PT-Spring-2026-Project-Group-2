#pragma once

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Player.h" 

class RebootRepairAction : public Action
{
public:
    RebootRepairAction(ApplicationManager* pApp); // constructor
    virtual bool ReadActionParameters(); // reads action data
    virtual void Execute(); // repairs the current player
    virtual ~RebootRepairAction(); // destructor
};