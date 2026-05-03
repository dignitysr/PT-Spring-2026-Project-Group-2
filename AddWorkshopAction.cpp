#include "AddWorkshopAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Workshop.h"  
#include <iostream>
AddWorkshopAction::AddWorkshopAction(ApplicationManager* pApp) : Action(pApp)
{
   
}

bool AddWorkshopAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Click on the cell to add a workshop");
    pos = pIn->GetCellClicked(); 

    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    if (pGrid->GetCell(pos)->GetGameObject() != nullptr) {
        pOut->PrintMessage("Cannot place the workshop on an occupied cell.");
        pIn->GetCellClicked(); pOut->ClearStatusBar(); return false;
    }

    pOut->ClearStatusBar();  
    return true;
}

void AddWorkshopAction::Execute()
{
    if (!ReadActionParameters()) return;

       
    Workshop* pWorkshop = new Workshop(pos);

    Grid* pGrid = pManager->GetGrid();
    bool added = pGrid->AddObjectToCell(pWorkshop);

    if (!added) {
        pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
    }
    else {
        pGrid->GetCell(pos)->DrawCellOrWaterPitOrDangerZone(pGrid->GetOutput());  
    }
}

AddWorkshopAction::~AddWorkshopAction()
{
    
}