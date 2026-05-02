#include "NewGameAction.h"
#include "GameState.h"
#include "Grid.h"
#include "Player.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
    // No parameters are needed, this action simply resets the game state.
}

void NewGameAction::Execute()
{
    // Get the current game state
    GameState* pGameState = pManager->GetGameState();
    Grid* pGrid = pManager->GetGrid();

    // Reset all players: set health, reset saved commands, set positions to the start cell
    for (int i = 0; i < MaxPlayerCount; i++)
    {
        Player* currentPlayer = pGameState->GetPlayer(i);

        // Reset health to 10 and clear saved commands
        currentPlayer->SetHealth(MaxHealth);
        currentPlayer->ClearSavedCommands();

        // Reset position to start cell
        Cell* startCell = pGrid->GetStartCell();
        currentPlayer->SetCell(startCell);
    }

    // Set player 1 as the first player
    pGameState->SetFirstPlayer(1);

    // Reset phase and end game state if needed
    pGameState->SetCurrentPhase(PHASE_MOVEMENT);
    pGameState->SetEndGame(false);

    // Update the interface to reflect the changes
    pGrid->UpdateInterface(pGameState);
}

NewGameAction::~NewGameAction()
{
}