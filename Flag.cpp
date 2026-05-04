#include "Flag.h"
#include "GameState.h"

Flag::Flag(const CellPosition & flagposition) : GameObject(flagposition)
{

}

void Flag::Draw(Output* pOut) const
{
	pOut->DrawFlag(position);
}

void Flag::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	pGrid->GetOutput()->PrintMessage("You have reached a flag. Click to continue ... ");//print the massege
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);//waiting for the  mouse click
	pGrid->GetOutput()->ClearStatusBar();
	pState->SetEndGame(true); // ENDGAME

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a flag. Click to continue ..." and wait mouse click

	// 2- Apply the flag's effect by ending the game
	//    Review the "pGrid" functions and decide which function can be used for that
}

void Flag::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:cell
	if (type == FLAG_TYPE) 
	OutFile << position.GetCellNum() << endl;
}

void Flag::Load(ifstream& InFile)
{
	int cellNum;
	if (InFile >> cellNum) // Read the cell number from the file
	{
		// Update the position using the helper function
		this->position = CellPosition::GetCellPositionFromNum(cellNum);
	}
}

Flag* Flag::Clone() const
{
	return new Flag(*this);
}

bool Flag::IsType(GameObjectType type) const { return type == FLAG_TYPE; }
Flag::~Flag()
{

}