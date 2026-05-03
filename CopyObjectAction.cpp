#include "CopyObjectAction.h"


CopyObjectAction::CopyObjectAction(ApplicationManager* pApp) : Action(pApp) {
	cellToCopy = nullptr;
}

bool CopyObjectAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Copy Object: Click on the cell to copy its object ...");
	cellToCopy = pGrid->GetCell(pIn->GetCellClicked());
	if (!cellToCopy) {
		pGrid->PrintErrorMessage("Error: Invalid cell selected! Click to continue ...");
		return false;
	}
	if (!cellToCopy->GetGameObject()) {
		pGrid->PrintErrorMessage("Error: No object in the selected cell! Click to continue ...");
		return false;
	}
	pOut->ClearStatusBar();
	return true;
}

void CopyObjectAction::Execute() {
	if (!ReadActionParameters()) return;
	Grid* pGrid = pManager->GetGrid();
	GameObject* gameObj = cellToCopy->GetGameObject();

	pGrid->SetClipboard(gameObj);
}

CopyObjectAction::~CopyObjectAction() {}