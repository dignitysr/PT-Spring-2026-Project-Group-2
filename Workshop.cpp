#include "Workshop.h"
#include "Player.h"
#include "Output.h"



Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO: Implement this function
	// Apply the workshop's effect on the player
	
	Output* pOut = pGrid->GetOutput();

	//start of addition
	//1.validity of player
	if (!pPlayer) return;

	//2.Landing on a workshop repairs the robot.
	pPlayer->SetHealth(MaxHealth);

	// 3.Feedback to the User
	pOut->PrintMessage("You reached a Workshop! Health repaired.");

	// [OPTIONAL BONUS] Consumables can be given to the player here
	
}

void Workshop::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:cell
	OutFile << position.GetCellNum() << endl;
}

void Workshop::Load(ifstream& InFile)
{
	int cellNum;
	if (InFile >> cellNum) // Read the cell number from the file
	{
		// Update the position using the helper function
		this->position = CellPosition::GetCellPositionFromNum(cellNum);
	}
}

Workshop::~Workshop()
{
}
