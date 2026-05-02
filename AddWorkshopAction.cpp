#include "AddWorkshopAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Workshop.h"  

AddWorkshopAction::AddWorkshopAction(ApplicationManager* pApp) : Action(pApp)
{
   
}

void AddWorkshopAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Click on the cell to add a workshop");
    pos = pIn->GetCellClicked(); 

    if (!pos.IsValidCell()) {
        pOut->PrintMessage("Invalid cell selection. Try again...");
        return;
    }

    if (pGrid->GetCell(pos) != nullptr) {
        pOut->PrintMessage("Cannot place the workshop on an occupied cell.");
        return;
    }

    pOut->ClearStatusBar();  
}

void AddWorkshopAction::Execute()
{
    ReadActionParameters();

    if (pos.IsValidCell() && pManager->GetGrid()->GetCell(pos) == nullptr) {

       
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
}

AddWorkshopAction::~AddWorkshopAction()
{
    
}