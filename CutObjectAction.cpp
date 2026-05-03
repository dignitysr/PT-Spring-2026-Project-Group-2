#include "CutObjectAction.h"


CutObjectAction::CutObjectAction(ApplicationManager* pApp) : Action(pApp) {
	cellToCut = nullptr;
}

bool CutObjectAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Cut Object: Click on the cell to cut its object ...");
	cellToCut = pGrid->GetCell(pIn->GetCellClicked());
	if (!cellToCut) {
		pGrid->PrintErrorMessage("Error: Invalid cell selected! Click to continue ...");
		return false;
	}
	if (!cellToCut->GetGameObject()) {
		pGrid->PrintErrorMessage("Error: No object in the selected cell! Click to continue ...");
		return false;
	}
	pOut->ClearStatusBar();
	return true;
}

void CutObjectAction::Execute() {
	if (!ReadActionParameters()) return;
	Grid* pGrid = pManager->GetGrid();
	GameObject* gameObj = cellToCut->GetGameObject();

	pGrid->SetClipboard(gameObj);
	pGrid->RemoveObjectFromCell(cellToCut->GetCellPosition());
}

CutObjectAction::~CutObjectAction() {}