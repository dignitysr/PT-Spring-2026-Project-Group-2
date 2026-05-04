#include "Player.h"

#include "GameObject.h"
#include "GameState.h"
#include <random>

Player::Player(Cell* pCell, int playerNum)
	: playerNum(playerNum), health(10), currDirection(RIGHT), savedCommandCount(0) , isHacked(false)
{
	this->pCell = pCell;

	// Initialise saved commands to NO_COMMAND
	for (int i = 0; i < MaxSavedCommandsWithExtendedMemory; i++)
		savedCommands[i] = NO_COMMAND;
}

// ====== Setters and Getters ======

void  Player::SetCell(Cell* cell)   { pCell = cell; }
Cell* Player::GetCell() const       { return pCell; }

void Player::SetHealth(int h)
{
	///TODO: Add validation (e.g. clamp to 0..MaxHealth)
	// done by abd el rahman
	health = max(0, min(h, MaxHealth));
}
int Player::GetHealth() const       { return health; }

Direction Player::GetDirection() const      { return currDirection; }
void      Player::SetDirection(Direction d) { currDirection = d; }

int Player::GetPlayerNum() const {return playerNum;}

void Player::AddToolkit(){ hasToolkit = true; }
void Player::AddHackDevice(){ hasHackDevice = true;}

bool Player::HasToolkit() const{ return hasToolkit; }
bool Player::HasHackDevice() const{ return hasHackDevice;}

void Player::UseToolkit(){ hasToolkit = false; }
void Player::UseHackDevice(){ hasHackDevice = false;}

void Player::SetHacked(bool value){	isHacked = value;}
bool Player::IsHacked() const{ return isHacked;}

// ====== Saved Commands ======

void Player::AddSavedCommand(Command cmd)
{
	if (savedCommandCount < GetMaxCommands())
		savedCommands[savedCommandCount++] = cmd;
}

void Player::ClearSavedCommands()
{
	for (int i = 0; i < MaxSavedCommandsWithExtendedMemory; i++)
		savedCommands[i] = NO_COMMAND;
	savedCommandCount = 0;
}

int     Player::GetSavedCommandCount() const { return savedCommandCount; }
Command Player::GetSavedCommand(int index) const
{
	if (index >= 0 && index < savedCommandCount)
		return savedCommands[index];
	return NO_COMMAND;
}

Command Player::GetAvailableCommand(int index) const
{
	if (index >= 0 && index < availabeCommandCount)
		return availableCommands[index];
	return NO_COMMAND;
}

int Player::GetAvailableCommandCount() const { return availabeCommandCount; }

void Player::RandomizeAvailableCommands()
{
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<> dis(0, COMMANDS_COUNT - 1);
	for (int i = 0; i < MaxAvailableCommands; i++) { 
		Command command = static_cast<Command>(dis(gen));
		while (command == NO_COMMAND) {
			command = static_cast<Command>(dis(gen));
		}
		availableCommands[i] = command;
	}
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	///TODO: Call the appropriate Output function to draw the player token with playerColor
	// done by abd el rahman
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor, currDirection);
}

void Player::DrawCommands(Output* pOut)
{
	pOut->CreateCommandsBar(savedCommands, savedCommandCount, availableCommands, availabeCommandCount);
}

void Player::ClearDrawing(Output* pOut) const
{
	///TODO: Determine the correct background colour for this cell
	//       (hint: may differ from UI.CellColor if cell is a WaterPit or DangerZone)
	// changed to determining correct cell type
	pCell->DrawCellOrWaterPitOrDangerZone(pOut);
	pCell->DrawGameObject(pOut);
	///TODO: Call the appropriate Output function to draw the token using cellColor (erases it)
}

// ====== Game Logic ======

void Player::ExecuteCommand(Command cmd, Grid* pGrid, GameState* pState) {
	CellPosition newPos = pCell->GetCellPosition();
	switch (cmd) {
		case MOVE_FORWARD_ONE_STEP:
			newPos.AddCellNum(1, currDirection);
			break;
		case MOVE_FORWARD_TWO_STEPS:
			newPos.AddCellNum(2, currDirection);
			break;
		case MOVE_FORWARD_THREE_STEPS:
			newPos.AddCellNum(3, currDirection);
			break;
		case MOVE_BACKWARD_ONE_STEP:
			newPos.AddCellNum(-1, currDirection);
			break;
		case MOVE_BACKWARD_TWO_STEPS:
			newPos.AddCellNum(-2, currDirection);
			break;
		case MOVE_BACKWARD_THREE_STEPS:
			newPos.AddCellNum(-3, currDirection);
			break;
		case ROTATE_CLOCKWISE:
			currDirection = static_cast<Direction>((currDirection + 1) % 4);
			break;
		case ROTATE_COUNTERCLOCKWISE:
			currDirection = static_cast<Direction>((currDirection + 3) % 4);
			break;
	}
	if (newPos.IsValidCell())	pGrid->UpdatePlayerCell(this, newPos);
	else pGrid->PrintErrorMessage("Invalid move: out of bounds");

	if (!pCell->HasWorkshop()) {
		GameObject* obj = pCell->GetGameObject();
		if (obj) obj->Apply(pGrid, pState, this);
	}

	pGrid->UpdateInterface(pState);
}

void Player::Move(Grid* pGrid, GameState* pState)
{

	int x, y;
	///TODO: Implement this function
	// - Execute the saved commands one by one, waiting for a mouse click between each
	// - After all commands are executed, apply the game object effect at the final cell (if any)
	// - Use CellPosition and Grid to handle movement and cell updates
	for (int i = 0; i < savedCommandCount; i++)
	{
		Command cmd = savedCommands[i];
		ExecuteCommand(cmd, pGrid, pState);
		pGrid->GetInput()->GetPointClicked(x, y); // wait for input
	}
	if (pCell->HasWorkshop()) {
		GameObject* obj = pCell->GetGameObject();
		if (obj) obj->Apply(pGrid, pState, this);
	}
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	// TODO: Modify the Info as needed
	playersInfo += "P" + to_string(playerNum) + "(";
	string dirStr = "";
	switch (currDirection) {
		case UP: dirStr = "UP"; break;
		case DOWN: dirStr = "DOWN"; break;
		case RIGHT: dirStr = "RIGHT"; break;
		case LEFT: dirStr = "LEFT"; break;
	}
	playersInfo += dirStr + ", ";
	playersInfo += to_string(health) + ")";
}
