#include "PasteObjectAction.h"
#include "GameObject.h"


PasteObjectAction::PasteObjectAction(ApplicationManager* pApp) : Action(pApp) {
	cellToPaste = nullptr;
}

bool PasteObjectAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Paste Object: Click on the cell to paste its object ...");
	cellToPaste = pGrid->GetCell(pIn->GetCellClicked());
	if (!cellToPaste) {
		pGrid->PrintErrorMessage("Error: Invalid cell selected! Click to continue ...");
		pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
	}
	if (cellToPaste->GetGameObject()) {
		pGrid->PrintErrorMessage("Error: There is an object in the selected cell! Click to continue ...");
		pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
	}
	pOut->ClearStatusBar();
	return true;
}

void PasteObjectAction::Execute() {
	if (!ReadActionParameters()) return;
	Grid* pGrid = pManager->GetGrid();
	GameObject* gameObj = pGrid->GetClipboard()->Clone();
	gameObj->SetPosition(cellToPaste->GetCellPosition(), pGrid);

	pGrid->AddObjectToCell(gameObj);
}

PasteObjectAction::~PasteObjectAction() {}