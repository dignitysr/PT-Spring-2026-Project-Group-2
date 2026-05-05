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
	pOut->PrintMessage("You've reached a workshop! Health restored. Click to continue ... ");
	pIn->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	pOut->PrintMessage("You can now purchase additional equipment or consumables. Click to continue ... ");
	pIn->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	// [OPTIONAL BONUS] Consumables can be given to the player here
	pOut->PrintMessage("Buy item: 0 Skip, 1 Extended Memory, 2 Toolkit, 3 Hack Device, 4 Double Laser.");
	pIn->GetCellClicked();
	pOut->PrintMessage("BEWARE: Each equipment or consumables will cost you 2 of your health! Click to continue ... ");
	pIn->GetCellClicked();
	pGrid->GetOutput()->ClearStatusBar();
	int choice = pIn->GetInteger(pOut);
	pOut->FlushMouseQueue();
	switch (choice) {
		case 1:
			if (pPlayer->HasExtendedMemory())//check if player has already extended his memory
			{
				pGrid->PrintErrorMessage("You already have Extended Memory. Click to continue ...");
			}
			else // if not
			{
				pPlayer->ActivateExtendedMemory();//extend his memory
				int newHealth = pPlayer->GetHealth() - 2;//decrease his health by 2
				pPlayer->SetHealth(newHealth);// setter for his new health
				pGrid->UpdateInterface(pState);// update interface
				pGrid->PrintErrorMessage("Extended Memory purchased. You can now save 6 commands. Click to continue ...");
			}
			break;
		case 2:
			{
			ToolKit * toolkit = new ToolKit(); //Make a ToolKit to give it to player if valid
			int newHealth = pPlayer->GetHealth() - 2;

			if (pPlayer->SetInventoryItem(toolkit)) { //If player can take a Toolkit
				pPlayer->SetHealth(newHealth);// setter for his new health
				pGrid->UpdateInterface(pState);// update interface
				pGrid->PrintErrorMessage("Toolkit purchased. Click to continue ...");
			}
			else {//if his Inventory is full
				pGrid->PrintErrorMessage("Inventory full! Cannot purchase Toolkit. Click to continue ...");
			}

			}
			break;
		case 3:
			{
			HackDevice* hackDevice = new HackDevice();//Make a hackDevice to give it to player if valid
			int newHealth = pPlayer->GetHealth() - 2;

			if (pPlayer->SetInventoryItem(hackDevice)) {//If player can take a hackDevice
				pPlayer->SetHealth(newHealth);// setter for his new health
				pGrid->UpdateInterface(pState);// update interface
				pGrid->PrintErrorMessage("Hack Device purchased. Click to continue ...");
			}
			else {//if his Inventory is full
				pGrid->PrintErrorMessage("Inventory full! Cannot purchase Hack Device. Click to continue ...");
			}

			}
			break;
		case 4:
			{
			DoubleLaser* doubleLaser = new DoubleLaser();//Make a doupleLaser to give it to player if valid
			int newHealth = pPlayer->GetHealth() - 2;

			if (pPlayer->SetInventoryItem(doubleLaser)) {//If player can take a doubleLaser
				pPlayer->SetHealth(newHealth);// setter for his new health
				pGrid->UpdateInterface(pState);// update interface
				pGrid->PrintErrorMessage("Double Laser purchased. Click to continue ...");
			}
			else {//if his Inventory is full
				pGrid->PrintErrorMessage("Inventory full! Cannot purchase Double Laser. Click to continue ...");
			}

			}
			break;
		default://player dont want any additional equipment or consumables
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
