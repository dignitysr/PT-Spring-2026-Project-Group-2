#include "AddDangerZoneAction.h"
#include "Grid.h"
#include "Cell.h"
#include "GameState.h"
#include "DangerZone.h"

AddDangerZoneAction::AddDangerZoneAction(ApplicationManager* pApp) : Action(pApp)
{

}

bool AddDangerZoneAction::ReadActionParameters()
{
    
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    
    pOut->PrintMessage("New Danger Zone: Click on the cell to place the Danger Zone ...");
    pos = pIn->GetCellClicked();  

    
    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    if (pGrid->GetCell(pos)->GetGameObject() != nullptr) {
        pOut->PrintMessage("Cannot place the Danger Zone on an occupied cell.");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    
    pOut->ClearStatusBar();
    return true;
}

void AddDangerZoneAction::Execute()
{
    
    if (!ReadActionParameters()) return;

    
        
    DangerZone* pDangerZone = new DangerZone(pos);  

        
    Grid* pGrid = pManager->GetGrid();
    bool added = pGrid->AddObjectToCell(pDangerZone);

        
    if (!added) {
        pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
    }
    else {
            
        pGrid->GetCell(pos)->DrawCellOrWaterPitOrDangerZone(pGrid->GetOutput());  
    }
}

AddDangerZoneAction::~AddDangerZoneAction()
{
    
}