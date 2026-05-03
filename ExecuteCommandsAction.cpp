#include "ExecuteCommandsAction.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"

ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* pApp) : Action(pApp)
{
    
}

bool ExecuteCommandsAction::ReadActionParameters()
{
    return true;
}


void ExecuteCommandsAction::Execute()
{
    
    Player* currentPlayer = pManager->GetGameState()->GetCurrentPlayer();

    int health = currentPlayer->GetHealth();


    if (commands.size() > health) {
        
        pManager->GetGrid()->GetOutput()->PrintMessage("Cannot select more commands than your health!");
        return;
    }

    
    for (int i = 0; i < commands.size(); i++) {
        
        if (commands[i] == "MOVE_FORWARD_ONE_STEP") {
            currentPlayer->AddSavedCommand(MOVE_FORWARD_ONE_STEP);
        }
        else if (commands[i] == "MOVE_FORWARD_TWO_STEPS") {
            currentPlayer->AddSavedCommand(MOVE_FORWARD_TWO_STEPS);
        }
        else if (commands[i] == "MOVE_FORWARD_THREE_STEPS") {
            currentPlayer->AddSavedCommand(MOVE_FORWARD_THREE_STEPS);
        }
        else if (commands[i] == "MOVE_BACKWARD_ONE_STEP") {
            currentPlayer->AddSavedCommand(MOVE_BACKWARD_ONE_STEP);
        }
        else if (commands[i] == "MOVE_BACKWARD_TWO_STEPS") {
            currentPlayer->AddSavedCommand(MOVE_BACKWARD_TWO_STEPS);
        }
        else if (commands[i] == "MOVE_BACKWARD_THREE_STEPS") {
            currentPlayer->AddSavedCommand(MOVE_BACKWARD_THREE_STEPS);
        }
        else if (commands[i] == "ROTATE_CLOCKWISE") {
            currentPlayer->AddSavedCommand(ROTATE_CLOCKWISE);
        }
        else if (commands[i] == "ROTATE_COUNTERCLOCKWISE") {
            currentPlayer->AddSavedCommand(ROTATE_COUNTERCLOCKWISE);
        }
        
    }

    currentPlayer->Move(pManager->GetGrid(), pManager->GetGameState());

  
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
    
}