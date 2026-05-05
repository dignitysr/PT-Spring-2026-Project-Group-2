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

	int toolKits = 0, hackDevices = 0, doubleLasers = 0;
	pPlayer->GetInventoryInfo(toolKits, hackDevices, doubleLasers);
	if (toolKits > 0 || hackDevices > 0 || doubleLasers > 0) {
		pOut->PrintMessage("You have " + to_string(toolKits) + " Toolkit(s), " + to_string(hackDevices) + " Hack Device(s), and " + to_string(doubleLasers) + " Double Laser(s). Click to continue ...");
		pIn->GetCellClicked(); // wait for input
	}

	if (toolKits > 0 || hackDevices > 0)
	{
		pOut->PrintMessage("Use consumable? 0 Cancel, 1 Toolkit, 2 Hack Device: ");
		int choice = pIn->GetInteger(pOut);

		switch (choice) { 
			case 1:
				if (toolKits > 0)
				{
					int toolKitIndex;
					Consumable* pToolkit = pPlayer->GetItemOfType(TOOLKIT, toolKitIndex);
					if (pToolkit)
					{
						pToolkit->ApplyEffect(pPlayer, pState);
						pPlayer->RemoveInventoryItem(toolKitIndex); // remove from inventory
						delete pToolkit; // free memory
					}
					pOut->PrintMessage("Toolkit used. Robot repaired. Click to continue ...");
				}
				else
				{
					pGrid->PrintErrorMessage("You do not have a Toolkit. Click to continue ...");
				}
				break;
			case 2:
				if (hackDevices > 0)
				{
					Player* opponent = pState->GetPlayer((pPlayer->GetPlayerNum() + 1) % MaxPlayerCount);
					int hackDeviceIndex;
					Consumable* pHackDevice = pPlayer->GetItemOfType(HACK_DEVICE, hackDeviceIndex);
					if (opponent != NULL)
					{
						pHackDevice->ApplyEffect(opponent, pState);
						pPlayer->RemoveInventoryItem(hackDeviceIndex); // remove from inventory
						delete pHackDevice; // free memory
					}
					pOut->PrintMessage("Hack Device used. Opponent will skip their next turn. Click to continue ...");
				}
				else
				{
					pGrid->PrintErrorMessage("You do not have a Hack Device. Click to continue ...");
				}
				break;
		}
	}
	pIn->GetCellClicked(); // wait for input
	pOut->ClearStatusBar();
	// keep track of the moving player
	Player* movingPlayer = pPlayer;

	pOut->FlushMouseQueue();

	// move using saved commands
	pPlayer->Move(pGrid, pState);

	if (pState->GetEndGame())
	{
		return;
	}


	pState->AdvancePhase();


	pPlayer->Shoot(pState, pGrid->GetOutput(), pGrid->GetInput());

	// redraw the interface
	pManager->UpdateInterface();
}

// destructor
ExecuteCommandsAction::~ExecuteCommandsAction()
{
}