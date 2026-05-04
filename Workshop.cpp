#include "Workshop.h"
#include "Player.h"
#include "Output.h"
#include "Input.h"
#include "Consumable.h"
#include "ToolKit.h"
#include "DoubleLaser.h"
#include "HackDevice.h"

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
	Input* pIn = pGrid->GetInput();
	//start of addition
	//1.validity of player
	if (!pPlayer) return;

	//2.Landing on a workshop repairs the robot.
	pPlayer->SetHealth(MaxHealth);

	// 3.Feedback to the User and Offers him to purchase additional equipment or consumables
	pOut->PrintMessage("You reached a Workshop! Health repaired. Click to continue ... .");
	pIn->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	pOut->PrintMessage("You can now purchase additional equipment or consumables IF WANTED .Click to continue ... ");
	pIn->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	// [OPTIONAL BONUS] Consumables can be given to the player here
	pOut->PrintMessage("Buy item: 0 Skip, 1 Extended Memory, 2 Toolkit, 3 Hack Device, 4 Double Laser NOTE:Each equipment or consumables cost you -1 of your health !. Click to continue ...  ");
	pIn->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	int choice = pIn->GetInteger(pOut);
	switch (choice) {
		case 1:
			if (pPlayer->HasExtendedMemory())
			{
				pGrid->PrintErrorMessage("You already have Extended Memory. Click to continue ...");
			}
			else
			{
				pPlayer->ActivateExtendedMemory();
				int newHealth = pPlayer->GetHealth() - 1;
				pPlayer->SetHealth(newHealth);
				pGrid->UpdateInterface(pState);
				pGrid->PrintErrorMessage("Extended Memory purchased. You can now save 6 commands. Click to continue ...");
			}
			break;
		case 2:
			{
			ToolKit * toolkit = new ToolKit();
			int newHealth = pPlayer->GetHealth() - 1;

			if (pPlayer->SetInventoryItem(toolkit)) {
				pPlayer->SetHealth(newHealth);
				pGrid->UpdateInterface(pState);
				pGrid->PrintErrorMessage("Toolkit purchased. Click to continue ...");
			}
			else {
				pGrid->PrintErrorMessage("Inventory full! Cannot purchase Toolkit. Click to continue ...");
			}

			}
			break;
		case 3:
			{
			HackDevice* hackDevice = new HackDevice();
			int newHealth = pPlayer->GetHealth() - 1;

			if (pPlayer->SetInventoryItem(hackDevice)) {
				pPlayer->SetHealth(newHealth);
				pGrid->UpdateInterface(pState);
				pGrid->PrintErrorMessage("Hack Device purchased. Click to continue ...");
			}
			else {
				pGrid->PrintErrorMessage("Inventory full! Cannot purchase Hack Device. Click to continue ...");
			}

			}
			break;
		case 4:
			{
			DoubleLaser* doubleLaser = new DoubleLaser();
			int newHealth = pPlayer->GetHealth() - 2;

			if (pPlayer->SetInventoryItem(doubleLaser)) {
				pPlayer->SetHealth(newHealth);
				pGrid->UpdateInterface(pState);
				pGrid->PrintErrorMessage("Double Laser purchased. Click to continue ...");
			}
			else {
				pGrid->PrintErrorMessage("Inventory full! Cannot purchase Double Laser. Click to continue ...");
			}

			}
			break;
		default:
			pGrid->PrintErrorMessage("Workshop action finished. Click to continue ...");
	
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
