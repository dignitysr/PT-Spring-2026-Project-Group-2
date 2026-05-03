#include "SwitchToDesignModeAction.h"
#include "Grid.h"
#include "Output.h"
#include "GameState.h"
#include "Player.h"


SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

bool SwitchToDesignModeAction::ReadActionParameters()
{
	// No parameters needed -- a mode switch requires no user input
	return true;
}

void SwitchToDesignModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	GameState* pState = pManager->GetGameState();

    for (int i = 0; i < MaxPlayerCount; i++)
    {
        Player* currentPlayer = pState->GetPlayer(i);

        // Reset health to 10 and clear saved commands
        currentPlayer->SetHealth(MaxHealth);
        currentPlayer->ClearSavedCommands();
        currentPlayer->SetDirection(RIGHT);

        // Reset position to start cell
        Cell* startCell = pGrid->GetStartCell();
        currentPlayer->SetCell(startCell);
    }

    // Set player 1 as the first player
    pState->SetFirstPlayer(1);

    // Reset phase and end game state if needed
    pState->SetCurrentPhase(PHASE_MOVEMENT);
    pState->SetEndGame(false);

	// 1. Switch the global interface mode to Design Mode
	UI.InterfaceMode = MODE_DESIGN;

	// 2. Redraw the toolbar with Design Mode buttons
	pOut->CreateDesignModeToolBar();

	// 3. Update the full interface so the grid is redrawn
	pManager->UpdateInterface();

	///TODO: Add any cleanup needed when leaving Play Mode.
}
SwitchToDesignModeAction::~SwitchToDesignModeAction()
{
}