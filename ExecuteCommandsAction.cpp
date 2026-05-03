#include "ExecuteCommandsAction.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"
#include "Output.h"

ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* pApp) : Action(pApp)
{
}

bool ExecuteCommandsAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();

	if (pPlayer == NULL)
	{
		pGrid->PrintErrorMessage("Error: No current player. Click to continue ...");
		return false;
	}

	if (pPlayer->GetSavedCommandCount() == 0)
	{
		pGrid->PrintErrorMessage("No saved commands to execute. Click to continue ...");
		return false;
	}

	return true;
}

void ExecuteCommandsAction::Execute()
{
	bool valid = ReadActionParameters();

	if (!valid)
		return;

	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();

	Player* pPlayer = pState->GetCurrentPlayer();

	Player* movingPlayer = pPlayer;

	pPlayer->Move(pGrid, pState);

	pPlayer->ClearSavedCommands();

	if (pState->GetCurrentPlayer() == movingPlayer)
	{
		pState->AdvanceCurrentPlayer();
	}

	pManager->UpdateInterface();
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
}