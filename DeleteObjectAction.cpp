#include "Action.h"
#include "DeleteObjectAction.h"

DeleteObjectAction::DeleteObjectAction(ApplicationManager* pApp):Action(pApp)
{
		celltodelete = nullptr;

}

bool DeleteObjectAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    pGrid->GetOutput()->PrintMessage("Delete Object: Click on the object you want to delete ...");

    
    celltodelete = pGrid->GetCell(pGrid->GetInput()->GetCellClicked());

    
    if (!celltodelete)
    {
        pGrid->PrintErrorMessage("Error: Invalid cell! Click to continue ...");
        return false;
    }

    
    if (!celltodelete->GetGameObject())
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
    delete pGrid->RemoveObjectFromCell(celltodelete->GetCellPosition());
    pGrid->GetOutput()->PrintMessage("Object deleted successfully!");
    pGrid->GetInput()->GetCellClicked();
    pGrid->GetOutput()->ClearStatusBar();

}

DeleteObjectAction::~DeleteObjectAction()
{
}

