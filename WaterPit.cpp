#include "WaterPit.h"
#include "Player.h"



WaterPit::WaterPit(const CellPosition & waterPitPosition):GameObject(waterPitPosition)
{
}

void WaterPit::Draw(Output * pOut) const
{
	pOut->DrawWaterPit(position);
}

void WaterPit::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	pGrid->GetOutput()->PrintMessage("You drowned in a water pit. Click to continue ... ");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	CellPosition startcell(4,0);
	pGrid->UpdatePlayerCell(pPlayer,startcell);
	int newhealth = pPlayer->GetHealth() - 3;
	pPlayer->SetHealth(newhealth);
	pGrid->UpdateInterface(pState);

	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message, make sure to edit this message according to which player wins "You drowned in a water pit. Player (0/1) wins !  Click to continue ..." and wait mouse click

	// 2- Apply the water pit's effect by setting the player's health which drowned to zero and ending the game
	// 3- Update the players info which is displayed (check Grid class and decide which function to use)

}

void WaterPit::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:cell
	if (type == WATER_PIT_TYPE) 
	OutFile << position.GetCellNum() << endl;
}

bool WaterPit::IsType(GameObjectType type) const { return type == WATER_PIT_TYPE; }

void WaterPit::Load(ifstream& InFile)
{
	int cellNum;
	if (InFile >> cellNum) // Read the cell number from the file
	{
		// Update the position using the helper function
		this->position = CellPosition::GetCellPositionFromNum(cellNum);
	}
}

WaterPit* WaterPit::Clone() const
{
	return new WaterPit(*this);
}


WaterPit::~WaterPit()
{
}
