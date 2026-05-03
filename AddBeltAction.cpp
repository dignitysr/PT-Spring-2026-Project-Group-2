#include "AddBeltAction.h"

AddBeltAction::AddBeltAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


bool AddBeltAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Belt: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Belt: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters
	if (!startPos.IsValidCell() || !endPos.IsValidCell()) {
		pOut->PrintMessage("invalid cell selection try again...");
		return false;
	
	}
	if (startPos == static_cast<CellPosition>(1)) {
		pOut->PrintMessage("Can't start the belt at cell 1.");
		return false;
	}
	if (startPos == endPos) {

		pOut->PrintMessage("Start and end positions cannot be the same.");

		return false;

	}
	if (pGrid->GetCell(startPos) != nullptr || pGrid->GetCell(endPos) != nullptr) {

		pOut->PrintMessage("Cannot place the belt on occupied cells.");

		return false;

	}
	if (startPos.VCell() != endPos.VCell() && startPos.HCell() != endPos.HCell()) {

		pOut->PrintMessage("Start and End positions must be in the same row or column.");

		return false;

	}
	if (pGrid->GetCell(endPos)->HasFlag()) {

		pOut->PrintMessage("Cannot place the belt at the flag.");

		return false;

	}

	// Clear messages
	pOut->ClearStatusBar();
	return true;
}

void AddBeltAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	if (!ReadActionParameters()) return;

	// Create a belt object with the parameters read from the user
	Belt * pBelt = new Belt(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

										
	bool added = pGrid->AddObjectToCell(pBelt);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the belt is created and added to the GameObject of its Cell, so we finished executing the AddBeltAction

}

AddBeltAction::~AddBeltAction()
{
}
