#include "SelectCommandAction.h"

#include "ApplicationManager.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "GameState.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>

// Constructor: Initializes the action with the ApplicationManager
SelectCommandAction::SelectCommandAction(ApplicationManager* pApp) : Action(pApp)
{

}

// Reads parameters: checks if player exists and has health
bool SelectCommandAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	Player* pPlayer = pState->GetCurrentPlayer();

	if (pPlayer == NULL || pPlayer->GetHealth() <= 0)
	{
		pGrid->PrintErrorMessage("Error: No current player or health. Click to continue ...");
		return false;
	}
	return true;
}

// Executes the action: allows player to select commands and saves them
void SelectCommandAction::Execute()
{
	if (!ReadActionParameters())
	{
		return;
	}

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	GameState* pState = pManager->GetGameState();

	Player* pPlayer = pState->GetCurrentPlayer();

	// Clear saved commands
	pPlayer->ClearSavedCommands();

	int maxCommandsToSelect = pPlayer->GetMaxCommands();
	int savedCount = 0;

	Command savedCommands[MaxSavedCommandsWithExtendedMemory];

	// Initialize saved commands
	for (int i = 0; i < maxCommandsToSelect; i++)
	{
		savedCommands[i] = NO_COMMAND;
	}

	Command availableCommands[MaxAvailableCommands];
	int availableCommandsCount = pPlayer->GetAvailableCommandCount();

	// Display available commands
	pOut->CreateCommandsBar(savedCommands, maxCommandsToSelect, availableCommands, availableCommandsCount);

	// Allow player to select commands
	while (savedCount < maxCommandsToSelect)
	{
		pOut->PrintMessage("Select a command. Click outside to stop.");

		int cmdIndex = pIn->GetSelectedCommandIndex();

		// Stop if clicked outside the commands
		if (cmdIndex == -1)
		{
			break;
		}

		// Check for invalid selection
		if (cmdIndex < 0 || cmdIndex >= availableCommandsCount)
		{
			pGrid->PrintErrorMessage("Invalid selection. Click to continue ...");
			continue;
		}

		// Save selected command
		Command selectedCmd = availableCommands[cmdIndex];
		pPlayer->AddSavedCommand(selectedCmd);

		savedCommands[savedCount] = selectedCmd;
		savedCount++;

		// Update displayed saved commands
		pOut->CreateCommandsBar(savedCommands, maxCommandsToSelect, availableCommands, availableCommandsCount);
	}

	// Inform player about selected commands
	if (savedCount == 0)
	{
		pGrid->PrintErrorMessage("No commands selected. Movement skipped.");
	}
	else
	{
		pGrid->PrintErrorMessage("Commands saved successfully.");
	}
}

// Destructor: Cleans up the action 
SelectCommandAction::~SelectCommandAction()
{
}