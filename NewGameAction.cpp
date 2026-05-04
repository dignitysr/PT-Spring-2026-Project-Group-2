#include "NewGameAction.h"
#include "GameState.h"
#include "Grid.h"
#include "Player.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
}

bool NewGameAction::ReadActionParameters()
{
    // No parameters are needed, this action simply resets the game state.
    return true;
}

void NewGameAction::Execute()
{
    // Get the current game state
    GameState* pGameState = pManager->GetGameState();
    Grid* pGrid = pManager->GetGrid();

    pGameState->ResetAllPlayers(pGrid);


    // Set player 1 as the first player
    pGameState->SetFirstPlayer(0);

    // Reset phase and end game state if needed
    pGameState->SetCurrentPhase(PHASE_MOVEMENT);
    pGameState->SetEndGame(false);

    // Update the interface to reflect the changes
    pGrid->UpdateInterface(pGameState);
}

NewGameAction::~NewGameAction()
{
}