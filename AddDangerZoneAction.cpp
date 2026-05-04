#include "AddDangerZoneAction.h"
#include "Grid.h"
#include "Cell.h"
#include "GameState.h"
#include "DangerZone.h"

// constructor
AddDangerZoneAction::AddDangerZoneAction(ApplicationManager* pApp) : Action(pApp)
{

}

// read danger zone position
bool AddDangerZoneAction::ReadActionParameters()
{

    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // ask user to choose a cell
    pOut->PrintMessage("New Danger Zone: Click on the cell to place the Danger Zone ...");
    pos = pIn->GetCellClicked();

    // check valid cell
    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    // check if cell already has an object
    if (pGrid->GetCell(pos)->GetGameObject() != nullptr) {
        pOut->PrintMessage("Cannot place the Danger Zone on an occupied cell.");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    // clear status bar
    pOut->ClearStatusBar();
    return true;
}

// add danger zone object
void AddDangerZoneAction::Execute()
{
    // read and validate position
    if (!ReadActionParameters()) return;

    // create danger zone object
    DangerZone* pDangerZone = new DangerZone(pos);

    // add object to grid
    Grid* pGrid = pManager->GetGrid();
    bool added = pGrid->AddObjectToCell(pDangerZone);

    // check if object was added
    if (!added) {
        pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
    }
    else {
        // draw the danger zone cell
        pGrid->GetCell(pos)->DrawCellOrWaterPitOrDangerZone(pGrid->GetOutput());
    }
}

// destructor
AddDangerZoneAction::~AddDangerZoneAction()
{

}