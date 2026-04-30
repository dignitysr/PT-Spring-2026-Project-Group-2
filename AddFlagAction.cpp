#include "AddFlagAction.h"



AddFlagAction::AddFlagAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddFlagAction::ReadActionParameters()
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

	pOut->PrintMessage("New Flag: Click on the cell to place the flag ...");
	CellPosition flagPos = pIn->GetCellClicked();

	if (!flagPos.IsValidCell()) {
		pOut->PrintMessage("Invalid cell selection for the flag. Try again...");
		return;
	}
	if (pGrid->GetCellObject(flagPos) != nullptr) {
		pOut->PrintMessage("Cell is already occupied, try a different cell.");
		return;
	}
	pOut->ClearStatusBar();
}

void AddFlagAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a flag object
	// 2-get a pointer to the Grid from the ApplicationManager
	// 3-Add the flag object to the GameObject of its Cell:
	// 4-Check if the flag was added and print an errror message if flag couldn't be added
	Flag* pFlag = new Flag(flagPos);

	Grid* pGrid = pManager->GetGrid()

	bool added = pGrid->AddObjectToCell(pFlag);
	if (!added) {

		pGrid->PrintErrorMessage("Error: Cell already has an object. Click to continue ...");

		return;

	}
	pGrid->PrintMessage("Flag added successfully!");

	pGrid->UpdateInterface();
}

AddFlagAction::~AddFlagAction()
{
}