#include "AddAntennaAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Antenna.h"

// constructor
AddAntennaAction::AddAntennaAction(ApplicationManager* pApp) : Action(pApp)
{

}

// read antenna position
bool AddAntennaAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // ask user to choose a cell
    pOut->PrintMessage("New Antenna: Click on the cell to place the Antenna ...");

    // get selected cell
    pos = pIn->GetCellClicked();

    // check valid cell
    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        pIn->GetCellClicked();
        pOut->ClearStatusBar();
        return false;
    }

    // check if cell already has an object
    if (pGrid->GetCell(pos)->GetGameObject() != nullptr) {
        pOut->PrintMessage("Cannot place the antenna on an occupied cell.");
        pIn->GetCellClicked();
        pOut->ClearStatusBar();
        return false;
    }

    // clear status bar
    pOut->ClearStatusBar();

    return true;
}

// add antenna object
void AddAntennaAction::Execute()
{
    // read and validate position
    if (!ReadActionParameters())
        return;

    // create antenna object
    Antenna* pAntenna = new Antenna(pos);

    Grid* pGrid = pManager->GetGrid();

    // add object to grid
    bool added = pGrid->AddObjectToCell(pAntenna);

    // check if object was added
    if (!added) {
        pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
    }
}

// destructor
AddAntennaAction::~AddAntennaAction()
{

}