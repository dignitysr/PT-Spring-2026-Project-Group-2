#include "AddFlagAction.h"
#include "CellPosition.h"
#include <iostream>


AddFlagAction::AddFlagAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


bool AddFlagAction::ReadActionParameters()
{
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces

	// 2- Read the flagPos

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (pGrid->FlagExists()) {
		pOut->PrintMessage("A flag already exists on the board. Cannot add another flag.");
		pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
	}

	pOut->PrintMessage("New Flag: Click on the cell to place the flag ...");
	flagPos = pIn->GetCellClicked();

	if (!flagPos.IsValidCell()) {
		pOut->PrintMessage("Invalid cell selection for the flag. Try again...");
		pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
	}
	if (pGrid->GetCell(flagPos)->GetGameObject() != nullptr) {
		pOut->PrintMessage("Cell is already occupied, try a different cell.");
		pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
	}
	pOut->ClearStatusBar();
	return true;
}

void AddFlagAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if (!ReadActionParameters()) return;
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a flag object
	// 2-get a pointer to the Grid from the ApplicationManager
	// 3-Add the flag object to the GameObject of its Cell:
	// 4-Check if the flag was added and print an errror message if flag couldn't be added
	Flag* pFlag = new Flag(flagPos);

	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pFlag);
	if (!added) {

		pGrid->PrintErrorMessage("Error: Cell already has an object. Click to continue ...");

		return;

	}

}

AddFlagAction::~AddFlagAction()
{
}