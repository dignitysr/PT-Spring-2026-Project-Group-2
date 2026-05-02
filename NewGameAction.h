#pragma once

#include "Action.h"
#include "GameState.h"
#include "Player.h"

class NewGameAction : public Action
{
public:
    NewGameAction(ApplicationManager* pApp);

    // Reads the parameters required for action to execute
    virtual void ReadActionParameters();

    // Executes the action of starting a new game
    virtual void Execute();

    // Virtual destructor
    virtual ~NewGameAction();
};