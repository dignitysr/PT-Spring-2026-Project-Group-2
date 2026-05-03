#include "AddWaterPitAction.h"
#include "Grid.h"
#include "GameState.h"
#include "WaterPit.h"  

AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) : Action(pApp)
{

}

bool AddWaterPitAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Click on the cell to add a water pit");
    pos = pIn->GetCellClicked();  

    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    if (pGrid->GetCell(pos)->GetGameObject() != nullptr) {
        pOut->PrintMessage("Cannot place the water pit on an occupied cell.");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    pOut->ClearStatusBar();  
    return true;
}

void AddWaterPitAction::Execute()
{
    
if (!ReadActionParameters()) return;


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

AddWaterPitAction::~AddWaterPitAction()
{
    
}