#include "AddWaterPitAction.h"
#include "Grid.h"
#include "GameState.h"
#include "WaterPit.h"  

// constructor
AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) : Action(pApp)
{

}

// read water pit position
bool AddWaterPitAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // ask user to choose a cell
    pOut->PrintMessage("Click on the cell to add a water pit");
    pos = pIn->GetCellClicked();

    // check valid cell
    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    // check if cell already has an object
    if (pGrid->GetCell(pos)->GetGameObject() != nullptr) {
        pOut->PrintMessage("Cannot place the water pit on an occupied cell.");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    // clear status bar
    pOut->ClearStatusBar();
    return true;
}

// add water pit object
void AddWaterPitAction::Execute()
{
    // read and validate position
    if (!ReadActionParameters()) return;

    // create water pit object
    WaterPit* pWaterPit = new WaterPit(pos);

    // add object to grid
    Grid* pGrid = pManager->GetGrid();
    bool added = pGrid->AddObjectToCell(pWaterPit);

    // check if object was added
    if (!added) {
        pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
    }
    else {
        // draw the water pit cell
        pGrid->GetCell(pos)->DrawCellOrWaterPitOrDangerZone(pGrid->GetOutput());
    }
}

// destructor
AddWaterPitAction::~AddWaterPitAction()
{

}