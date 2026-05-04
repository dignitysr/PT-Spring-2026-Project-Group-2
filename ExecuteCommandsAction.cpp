#include "ExecuteCommandsAction.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"
#include "Output.h"

// constructor
ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* pApp) : Action(pApp)
{
}

// check if there are saved commands to execute
bool ExecuteCommandsAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();

	// check current player
	if (pPlayer == NULL)
	{
		pGrid->PrintErrorMessage("Error: No current player. Click to continue ...");
		return false;
	}

	// check saved commands
	if (pPlayer->GetSavedCommandCount() == 0)
	{
		pGrid->PrintErrorMessage("No saved commands to execute. Click to continue ...");
		return false;
	}

	return true;
}

// execute the saved commands
void ExecuteCommandsAction::Execute()
{
	// validate before execution
	bool valid = ReadActionParameters();

	if (!valid)
		return;

	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();

	Player* pPlayer = pState->GetCurrentPlayer();

	// keep track of the moving player
	Player* movingPlayer = pPlayer;

	// move using saved commands
	pPlayer->Move(pGrid, pState);

	// clear commands after execution
	pPlayer->ClearSavedCommands();

	// advance turn only if the current player was not changed by another object
	if (pState->GetCurrentPlayer() == movingPlayer)
	{
		pState->AdvanceCurrentPlayer();
	}

	// redraw the interface
	pManager->UpdateInterface();
}

// destructor
ExecuteCommandsAction::~ExecuteCommandsAction()
{
}