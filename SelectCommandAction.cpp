#include "SelectCommandAction.h"

#include "ApplicationManager.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "GameState.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>

SelectCommandAction::SelectCommandAction(ApplicationManager* pApp) : Action(pApp)
{

}

bool SelectCommandAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();

	Player* pPlayer = pState->GetCurrentPlayer();

	if (pPlayer == NULL)
	{
		pGrid->PrintErrorMessage("Error: No current player. Click to continue ...");
		return false;
	}

	int health = pPlayer->GetHealth();

	if (health <= 0)
	{
		pGrid->PrintErrorMessage("Player has no health points. Click to continue ...");
		return false;
	}
	return true;
}

void SelectCommandAction::Execute()
{
	bool valid = ReadActionParameters();

	if (!valid)
	{
		return;
	}

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	GameState* pState = pManager->GetGameState();

	Player* pPlayer = pState->GetCurrentPlayer();

	if (pPlayer == NULL)
	{
		pGrid->PrintErrorMessage("Error: No current player. Click to continue ...");
		return;
	}

	pPlayer->ClearSavedCommands();

	int maxCommandsToSelect = pPlayer->GetMaxCommands();

	if (pPlayer->GetHealth() < maxCommandsToSelect)
	{
		maxCommandsToSelect = pPlayer->GetHealth();
	}

	Command savedCommands[MaxSavedCommandsWithExtendedMemory];

	for (int i = 0; i < MaxSavedCommandsWithExtendedMemory; i++)
	{
		savedCommands[i] = NO_COMMAND;
	}

	int savedCount = 0;

	Command availableCommands[MaxAvailableCommands];
	int availableCommandsCount = pPlayer->GetAvailableCommandCount();

	for (int i = 0; i < availableCommandsCount; i++)
	{
		availableCommands[i] = pPlayer->GetAvailableCommand(i);
	}

	pOut->CreateCommandsBar(savedCommands, maxCommandsToSelect, availableCommands, availableCommandsCount);

	while (savedCount < maxCommandsToSelect)
	{
		pOut->PrintMessage("Select a command from Available Commands. Click outside commands to stop.");

		int cmdIndex = pIn->GetSelectedCommandIndex();

		if (cmdIndex == -1)
		{
			break;
		}

		if (cmdIndex < 0 || cmdIndex >= availableCommandsCount)
		{
			pGrid->PrintErrorMessage("Invalid command selection. Click to continue ...");
			pOut->CreateCommandsBar(savedCommands, maxCommandsToSelect, availableCommands, availableCommandsCount);
			continue;
		}

		Command selectedCmd = availableCommands[cmdIndex];

		pPlayer->AddSavedCommand(selectedCmd);

		savedCommands[savedCount] = selectedCmd;
		savedCount++;

		pOut->CreateCommandsBar(savedCommands, maxCommandsToSelect, availableCommands, availableCommandsCount);
	}

	if (savedCount == 0)
	{
		pGrid->PrintErrorMessage("No commands selected. Movement phase skipped. Click to continue ...");
	}
	else
	{
		pGrid->PrintErrorMessage("Commands saved successfully. Click to continue ...");
	}
}

SelectCommandAction::~SelectCommandAction()
{
}