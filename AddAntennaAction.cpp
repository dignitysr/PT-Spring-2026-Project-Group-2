#include "AddAntennaAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Antenna.h"

AddAntennaAction::AddAntennaAction(ApplicationManager* pApp) : Action(pApp)
{
    
}

void AddAntennaAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("New Antenna: Click on the cell to place the Antenna ...");
    pos = pIn->GetCellClicked();  

    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        return;
    }

    if (pGrid->GetCell(pos) != nullptr) {
        pOut->PrintMessage("Cannot place the antenna on an occupied cell.");
        return;
    }

    pOut->ClearStatusBar();  
}

void AddAntennaAction::Execute()
{
    ReadActionParameters();

    if (pos.IsValidCell() && pManager->GetGrid()->GetCell(pos) == nullptr) {

        Antenna* pAntenna = new Antenna(pos);

        Grid* pGrid = pManager->GetGrid();
        bool added = pGrid->AddObjectToCell(pAntenna);

        
        if (!added) {
            pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
        }
    
    }
}

AddAntennaAction::~AddAntennaAction()
{
   
}