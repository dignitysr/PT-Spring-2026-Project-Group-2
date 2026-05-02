#include "AddWaterPitAction.h"
#include "Grid.h"
#include "GameState.h"
#include "WaterPit.h"  

AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) : Action(pApp)
{

}

void AddWaterPitAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Click on the cell to add a water pit");
    pos = pIn->GetCellClicked();  

    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        return;
    }

    if (pGrid->GetCell(pos) != nullptr) {
        pOut->PrintMessage("Cannot place the water pit on an occupied cell.");
        return;
    }

    pOut->ClearStatusBar();  
}

void AddWaterPitAction::Execute()
{
    
    ReadActionParameters();

    if (pos.IsValidCell() && pManager->GetGrid()->GetCell(pos) == nullptr) {

        WaterPit* pWaterPit = new WaterPit(pos);

        Grid* pGrid = pManager->GetGrid();
        bool added = pGrid->AddObjectToCell(pWaterPit);

        if (!added) {
            pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
        }
        else {
           
            pGrid->GetCell(pos)->DrawCellOrWaterPitOrDangerZone(pGrid->GetOutput());  
        }
    }
}

AddWaterPitAction::~AddWaterPitAction()
{
    
}