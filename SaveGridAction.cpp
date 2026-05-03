#include "SaveGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) :Action(pApp)
{
	//it stays empty
}

void SaveGridAction::ReadActionParameters()
{
	//pointers to input & output to interact with screen
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//receiving the file name from the user
	pOut->PrintMessage("Enter filename:   ");

	//using GetString() to recieve what the user types and concatenate .txt with it to make it a file
	filename = pIn->GetString(pOut) + ".txt";
}

void SaveGridAction::Execute()
{
	//Calling the Function to get the filename
	ReadActionParameters();
	
	//creating a "output file stream" object to write on
	ofstream OutFile(filename);

	//check for file validity and creation
	if (OutFile.is_open())
	{
		//get grid pointer
		Grid* pGrid = pManager->GetGrid();

		//This Action tells the Grid to save itself (polymorphism used)
		//tell the grid to save and loop throughout all cells and call save()
		pGrid->SaveAll(OutFile);

		//closing file to save & free memory
		OutFile.close();

		pGrid->PrintErrorMessage("Grid saved successfully to" + filename + ". Click to continue");
	}
	else
		pManager->GetGrid()->PrintErrorMessage("Error: Unable to create file!");
}

SaveGridAction::~SaveGridAction()
{
}
