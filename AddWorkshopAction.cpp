#include "AddWorkshopAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Workshop.h"  
#include <iostream>

// constructor
AddWorkshopAction::AddWorkshopAction(ApplicationManager* pApp) : Action(pApp)
{

}

// read workshop position
bool AddWorkshopAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // ask user to choose a cell
    pOut->PrintMessage("Click on the cell to add a workshop");
    pos = pIn->GetCellClicked();

    // check valid cell
    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    // check if cell already has an object
    if (pGrid->GetCell(pos)->GetGameObject() != nullptr) {
        pOut->PrintMessage("Cannot place the workshop on an occupied cell.");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    // clear status bar
    pOut->ClearStatusBar();
    return true;
}

// add workshop object
void AddWorkshopAction::Execute()
{
    // read and validate position
    if (!ReadActionParameters()) return;

    // create workshop object
    Workshop* pWorkshop = new Workshop(pos);

    // add object to grid
    Grid* pGrid = pManager->GetGrid();
    bool added = pGrid->AddObjectToCell(pWorkshop);

    // check if object was added
    if (!added) {
        pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
    }
    else {
        // draw the workshop cell
        pGrid->GetCell(pos)->DrawCellOrWaterPitOrDangerZone(pGrid->GetOutput());
    }
}

// destructor
AddWorkshopAction::~AddWorkshopAction()
{

}