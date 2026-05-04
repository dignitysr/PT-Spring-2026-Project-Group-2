#include "ExecuteCommandsAction.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"
#include "Output.h"
#include "Input.h"

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

	// check if player is hacked
	if (pPlayer->IsHacked())
	{
		pPlayer->SetHacked(false);
		pPlayer->ClearSavedCommands();
		pGrid->PrintErrorMessage("This player is hacked and skips this turn. Click to continue ...");

		pState->AdvanceCurrentPlayer();
		pManager->UpdateInterface();
		return;
	}

	// use consumable before executing commands
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (pPlayer->HasToolkit() || pPlayer->HasHackDevice())
	{
		pOut->PrintMessage("Use consumable? 0 Cancel, 1 Toolkit, 2 Hack Device: ");
		int choice = pIn->GetInteger(pOut);

		if (choice == 1)
		{
			if (pPlayer->HasToolkit())
			{
				pPlayer->SetHealth(MaxHealth);
				pPlayer->UseToolkit();
				pGrid->PrintErrorMessage("Toolkit used. Robot repaired. Click to continue ...");
			}
			else
			{
				pGrid->PrintErrorMessage("You do not have a Toolkit. Click to continue ...");
			}
		}
		else if (choice == 2)
		{
			if (pPlayer->HasHackDevice())
			{
				Player* opponent = pState->GetPlayer((pPlayer->GetPlayerNum() + 1) % MaxPlayerCount);

				if (opponent != NULL)
				{
					opponent->SetHacked(true);
				}

				pPlayer->UseHackDevice();
				pGrid->PrintErrorMessage("Hack Device used. Opponent will skip their next turn. Click to continue ...");
			}
			else
			{
				pGrid->PrintErrorMessage("You do not have a Hack Device. Click to continue ...");
			}
		}
	}

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