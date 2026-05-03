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

	pGrid->GetOutput()->PrintMessage("You have reached a flag. Click to continue ... ");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	pState->SetEndGame(true);

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a flag. Click to continue ..." and wait mouse click

	// 2- Apply the flag's effect by ending the game
	//    Review the "pGrid" functions and decide which function can be used for that
}

void Flag::Save(ofstream& OutFile) 
{
	OutFile << FLAG_TYPE << " " << position.GetCellNum() << endl;
}

Flag::~Flag()
{

}