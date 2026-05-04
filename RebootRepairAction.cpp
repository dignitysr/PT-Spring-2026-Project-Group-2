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
    pManager->GetGrid()->GetOutput()->PrintMessage("Reboot and repair your robot!");
    return true;
}

// repair the current player's robot
void RebootRepairAction::Execute()
{
    // get current player
    Player* currentPlayer = pManager->GetGameState()->GetCurrentPlayer();

    // increase health by 3 without exceeding max health
    int currentHealth = currentPlayer->GetHealth();
    int newHealth = std::min(currentHealth + 3, MaxHealth);

    // update player health
    currentPlayer->SetHealth(newHealth);

    // show updated health
    pManager->GetGrid()->GetOutput()->PrintMessage("Robot repaired! Health: " + std::to_string(newHealth));

}

// destructor
RebootRepairAction::~RebootRepairAction()
{

}