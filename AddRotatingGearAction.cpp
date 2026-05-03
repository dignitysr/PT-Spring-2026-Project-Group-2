#include "AddRotatingGearAction.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager * pApp):Action(pApp)
{
}

bool AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces

	// 2- Read the gearPos
	// 3- Read whether the direction will be clockwise or not

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Rotating Gear: Click on the cell to place the gear ...");
	gearPos = pIn->GetCellClicked();

	if (!gearPos.IsValidCell()) {
		pOut->PrintMessage("Invalid cell selection for the gear. Try again...");
		pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
	}
	if (pGrid->GetCell(gearPos)->GetGameObject() != nullptr) {
		pOut->PrintMessage("Cell is already occupied. Try a different cell.");
		pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
	}
	pOut->PrintMessage("Click to set the rotation direction (clockwise or counter-clockwise)...");
	pOut->PrintMessage("Enter 1 for clockwise, 0 for anti-clockwise: ");
	int dir = pIn->GetInteger(pOut);

	if (dir == 1)
		clockwise = true;
	else if (dir == 0)
		clockwise = false;
	else
	{
		pOut->PrintMessage("Invalid direction. Click to continue ...");
		pIn->GetCellClicked();
		return false;
	}
	pOut->ClearStatusBar();
	return true;
}
void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if (!ReadActionParameters()) return;
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a rotating gear object
	// 2-get a pointer to the Grid from the ApplicationManager
	// 3-Add the rotating object to the GameObject of its Cell:
	// 4-Check if the rotating gear was added and print an errror message if flag couldn't be added
	RotatingGear* pGear = new RotatingGear(gearPos, clockwise);

	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pGear);

	if (!added) {
		pGrid->PrintErrorMessage("Error: Cell already has an object. Click to continue ...");
		return;
	}

}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
