#include "CutObjectAction.h"


CutObjectAction::CutObjectAction(ApplicationManager* pApp) : Action(pApp) {
	cellToCut = nullptr;
}

void CutObjectAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Cut Object: Click on the cell to cut its object ...");
	cellToCut = pGrid->GetCell(pIn->GetCellClicked());
}

void CutObjectAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	if (!cellToCut) {
		pGrid->PrintErrorMessage("Error: Invalid cell selected! Click to continue ...");
		return;
	}
	GameObject* gameObj = cellToCut->GetGameObject();

	if (gameObj) {
		pGrid->SetClipboard(gameObj);
		pGrid->RemoveObjectFromCell(cellToCut->GetCellPosition());
	}
	else pGrid->PrintErrorMessage("Error: No object in the selected cell! Click to continue ...");
}

CutObjectAction::~CutObjectAction() {}