#include "Action.h"
#include "Grid.h"
#include "DeleteObjectAction.h"
#include "GameObject.h"
#include "Belt.h"
#include <iostream>

DeleteObjectAction::DeleteObjectAction(ApplicationManager* pApp):Action(pApp)//constructor
{
		celltodelete = nullptr;

}

bool DeleteObjectAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    pGrid->GetOutput()->PrintMessage("Delete Object: Click on the object you want to delete ...");

    celltodelete = pGrid->GetCell(pGrid->GetInput()->GetCellClicked());//Get the cell to delete

    
    if (!celltodelete)//if cell is selected is wrong
    {
        pGrid->PrintErrorMessage("Error: Invalid cell! Click to continue ...");
        return false;
    }

    
    if (!celltodelete->GetGameObject())//if cell already empty //has no gameobj
    {
        pGrid->PrintErrorMessage("Error: Cell is already empty! Click to continue ...");
        return false;
    }

    return true;
}

void DeleteObjectAction::Execute()
{
    if (!ReadActionParameters())
    {
        return;
    }
    Grid* pGrid = pManager->GetGrid();
    //delete object action

    if (celltodelete->GetGameObject()->IsType(BELT_TYPE))
    {
		Belt* belt = dynamic_cast<Belt*>(celltodelete->GetGameObject());
        if (belt->GetEndPosition() == celltodelete->GetCellPosition()) {
            pGrid->GetOutput()->PrintMessage("Please do not delete the end of a belt!");
            pGrid->GetInput()->GetCellClicked();
            pGrid->GetOutput()->ClearStatusBar();
            return;
        } else pGrid->RemoveObjectFromCell(belt->GetEndPosition());
    }

    delete pGrid->RemoveObjectFromCell(celltodelete->GetCellPosition());// no memory leak !!!!

    pGrid->GetOutput()->PrintMessage("Object deleted successfully!");
    pGrid->GetInput()->GetCellClicked();
    pGrid->GetOutput()->ClearStatusBar();

}

DeleteObjectAction::~DeleteObjectAction()
{
}

