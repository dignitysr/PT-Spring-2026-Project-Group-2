#include "CopyObjectAction.h"


CopyObjectAction::CopyObjectAction(ApplicationManager* pApp) : Action(pApp) {
	cellToCopy = nullptr;
}

void CopyObjectAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Copy Object: Click on the cell to copy its object ...");
	cellToCopy = pGrid->GetCell(pIn->GetCellClicked());
}

void CopyObjectAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	if (!cellToCopy) {
		pGrid->PrintErrorMessage("Error: Invalid cell selected! Click to continue ...");
		return;
	}
	GameObject* gameObj = cellToCopy->GetGameObject();

	if (gameObj) pGrid->SetClipboard(gameObj);
	else pGrid->PrintErrorMessage("Error: No object in the selected cell! Click to continue ...");
}

CopyObjectAction::~CopyObjectAction() {}