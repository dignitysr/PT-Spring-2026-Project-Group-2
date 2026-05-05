#include "RebootRepairAction.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"
#include <algorithm> 
#undef min
#undef max

// constructor
RebootRepairAction::RebootRepairAction(ApplicationManager* pApp) : Action(pApp)
{

}

// read repair action parameters
bool RebootRepairAction::ReadActionParameters()
{
    // show repair message
    Player* currentPlayer = pManager->GetGameState()->GetCurrentPlayer();
    Output* pOut = pManager->GetGrid()->GetOutput();
    Input* pIn = pManager->GetGrid()->GetInput();

	if (currentPlayer->GetUsedRepair()) {
        pOut->PrintMessage("You have already used your repair action for this round!");
        pIn->GetCellClicked(); // wait for user
        pOut->ClearStatusBar();
        return false;
    }

    pManager->GetGrid()->GetOutput()->PrintMessage("Reboot and repair your robot!");
    return true;
}

// repair the current player's robot
void RebootRepairAction::Execute()
{
	if (!ReadActionParameters()) return;
    // get current player
    Player* currentPlayer = pManager->GetGameState()->GetCurrentPlayer();

	Output* pOut = pManager->GetGrid()->GetOutput();
	Input* pIn = pManager->GetGrid()->GetInput();

    // increase health by 3 without exceeding max health
    int currentHealth = currentPlayer->GetHealth();
    int newHealth = std::min(currentHealth + 3, MaxHealth);

    // update player health
    currentPlayer->SetHealth(newHealth);
	currentPlayer->SetUsedRepair(true);

    // show updated health
    pOut->PrintMessage("Robot repaired! Health: " + std::to_string(newHealth));
	pIn->GetCellClicked(); // wait for user
    pOut->ClearStatusBar();


}

// destructor
RebootRepairAction::~RebootRepairAction()
{

}