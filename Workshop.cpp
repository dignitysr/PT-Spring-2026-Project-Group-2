#include "Workshop.h"
#include "Player.h"
#include "Output.h"
#include "Input.h"

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
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter 1 to buy Extended Memory, or 0 to skip: ");
	int choice = pIn->GetInteger(pOut);

	if (choice == 1)
	{
		if (pPlayer->HasExtendedMemory())
		{
			pGrid->PrintErrorMessage("You already have Extended Memory. Click to continue ...");
		}
		else
		{
			pPlayer->ActivateExtendedMemory();
			pGrid->PrintErrorMessage("Extended Memory purchased. You can now save 6 commands. Click to continue ...");
		}
	}
}

void Workshop::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:cell
	if (type == WORKSHOP_TYPE)
	OutFile << position.GetCellNum() << endl;
}
bool Workshop::IsType(GameObjectType type) const { return type == WORKSHOP_TYPE; }

void Workshop::Load(ifstream& InFile)
{
	int cellNum;
	if (InFile >> cellNum) // Read the cell number from the file
	{
		// Update the position using the helper function
		this->position = CellPosition::GetCellPositionFromNum(cellNum);
	}
}

Workshop* Workshop::Clone() const
{
	return new Workshop(*this);
}

Workshop::~Workshop()
{
}
