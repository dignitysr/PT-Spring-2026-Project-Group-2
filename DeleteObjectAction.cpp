#include "Action.h"
#include "DeleteObjectAction.h"

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
    //delete object action
    delete pGrid->RemoveObjectFromCell(celltodelete->GetCellPosition());
    delete pGrid->RemoveObjectFromCell(celltodelete->GetCellPosition());// no memory leak !!!!
    pGrid->GetOutput()->PrintMessage("Object deleted successfully!");
    delete pGrid->RemoveObjectFromCell(celltodelete->GetCellPosition());
    pGrid->GetInput()->GetCellClicked();
    pGrid->GetOutput()->ClearStatusBar();
    pGrid->GetOutput()->PrintMessage("Object deleted successfully!");

}

DeleteObjectAction::~DeleteObjectAction()
{
}

