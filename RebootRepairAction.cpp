#include "RebootRepairAction.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"
#include <algorithm> 
#undef min
#undef max

RebootRepairAction::RebootRepairAction(ApplicationManager* pApp) : Action(pApp)
{
    
}

void RebootRepairAction::ReadActionParameters()
{
    
    pManager->GetGrid()->GetOutput()->PrintMessage("Reboot and repair your robot!");
}

void RebootRepairAction::Execute()
{
    Player* currentPlayer = pManager->GetGameState()->GetCurrentPlayer();

  
    int currentHealth = currentPlayer->GetHealth();
    int newHealth = std::min(currentHealth + 3, MaxHealth);  
    currentPlayer->SetHealth(newHealth);  

    pManager->GetGrid()->GetOutput()->PrintMessage("Robot repaired! Health: " + std::to_string(newHealth));

}

RebootRepairAction::~RebootRepairAction()
{
   
}