#include "SelectCommandAction.h"
#include "Grid.h"
#include "Player.h"
#include "GameState.h"

std::string ActionTypeToString(ActionType action) {
    switch (action) {
    case ADD_BELT: return "ADD_BELT";
    case ADD_ANTENNA: return "ADD_ANTENNA";
    case ADD_DANGER_ZONE: return "ADD_DANGER_ZONE";
    case ADD_WATER_PIT: return "ADD_WATER_PIT";
    case ADD_WORKSHOP: return "ADD_WORKSHOP";
    default: return "UNKNOWN";
    }
}

Command stringToCommand(const std::string& commandStr) {
    if (commandStr == "MOVE_FORWARD_ONE_STEP") return MOVE_FORWARD_ONE_STEP;
    if (commandStr == "MOVE_FORWARD_TWO_STEPS") return MOVE_FORWARD_TWO_STEPS;
    if (commandStr == "MOVE_FORWARD_THREE_STEPS") return MOVE_FORWARD_THREE_STEPS;
    if (commandStr == "MOVE_BACKWARD_ONE_STEP") return MOVE_BACKWARD_ONE_STEP;
    if (commandStr == "MOVE_BACKWARD_TWO_STEPS") return MOVE_BACKWARD_TWO_STEPS;
    if (commandStr == "MOVE_BACKWARD_THREE_STEPS") return MOVE_BACKWARD_THREE_STEPS;
    if (commandStr == "ROTATE_CLOCKWISE") return ROTATE_CLOCKWISE;
    if (commandStr == "ROTATE_COUNTERCLOCKWISE") return ROTATE_COUNTERCLOCKWISE;
    return NO_COMMAND;
}

SelectCommandAction::SelectCommandAction(ApplicationManager* pApp) : Action(pApp) {}

bool SelectCommandAction::ReadActionParameters() {
    Player* currentPlayer = pManager->GetGameState()->GetCurrentPlayer();
    int health = currentPlayer->GetHealth();
    int maxCommands = (health < 5) ? health : 5;

    availableCommands = { "MOVE_FORWARD_ONE_STEP", "MOVE_FORWARD_TWO_STEPS", "MOVE_FORWARD_THREE_STEPS",
                         "MOVE_BACKWARD_ONE_STEP", "MOVE_BACKWARD_TWO_STEPS", "MOVE_BACKWARD_THREE_STEPS",
                         "ROTATE_CLOCKWISE", "ROTATE_COUNTERCLOCKWISE" };

    pManager->GetGrid()->GetOutput()->PrintMessage("Select up to " + std::to_string(maxCommands) + " commands.");

    for (int i = 0; i < maxCommands; i++) {
        std::string selectedCommand = ActionTypeToString(pManager->GetGrid()->GetInput()->GetUserAction());
        selectedCommands.push_back(selectedCommand);
    }

    for (int i = 0; i < selectedCommands.size(); i++) {
        currentPlayer->AddSavedCommand(stringToCommand(selectedCommands[i]));
    }
    return true;
}

void SelectCommandAction::Execute() {
    if (!ReadActionParameters()) return;
    Player* currentPlayer = pManager->GetGameState()->GetCurrentPlayer();
    currentPlayer->Move(pManager->GetGrid(), pManager->GetGameState());
}

SelectCommandAction::~SelectCommandAction() {}