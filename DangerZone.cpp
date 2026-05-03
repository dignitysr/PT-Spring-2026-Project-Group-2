#include "DangerZone.h"
#include "Player.h"


DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}

void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}

void DangerZone::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	pGrid->GetOutput()->PrintMessage("You have reached a danger zone. Click to continue ... ");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	int newhealth = pPlayer->GetHealth()-1;
	pPlayer->SetHealth(newhealth);
	pGrid->UpdateInterface(pState);


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a danger zone. Click to continue ..." and wait mouse click

	// 2- Apply the danger zone's effect by reducing the health of the player by 1 
	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
}

void DangerZone::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:cell
	if (type != DANGER_ZONE_TYPE) return;
	OutFile << position.GetCellNum() << endl;
}

void DangerZone::Load(ifstream& InFile)
{
	int cellNum;
	if (InFile >> cellNum) // Read the cell number from the file
	{
		// Update the position using the helper function
		this->position = CellPosition::GetCellPositionFromNum(cellNum);
	}
}

bool DangerZone::IsType(GameObjectType type) const { return type == DANGER_ZONE_TYPE; }
DangerZone::~DangerZone()
{
}
