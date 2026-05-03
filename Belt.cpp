#include "Belt.h"


Belt::Belt(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}
void Belt::Draw(Output* pOut) const
{
	pOut->DrawBelt(position, endCellPos);
}

void Belt::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	pGrid->GetOutput()->PrintMessage("You have reached a danger zone. Click to continue ... ");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a belt. Click to continue ..." and wait mouse click

	// 2- Apply the belt's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
}
CellPosition Belt::GetEndPosition() const
{
	return endCellPos;
}

void Belt::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:start_cell  end_cell
	if (type == BELT_TYPE) 	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl; 
}
void Belt::Load(ifstream& InFile) {
	int startCell, endCell;
	InFile >> startCell >> endCell;

	// Update the start position (inherited from GameObject)
	this->position = CellPosition::GetCellPositionFromNum(startCell);

	// Update the end position (specific to Belt)
	this->endCellPos = CellPosition::GetCellPositionFromNum(endCell);
}

bool Belt::IsType(GameObjectType type) const { return type == BELT_TYPE;}

Belt* Belt::Clone() const
{
	return new Belt(*this);
}


Belt::~Belt()
{
}
