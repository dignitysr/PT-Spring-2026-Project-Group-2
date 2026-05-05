#include "SaveGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) :Action(pApp)
{
	//it stays empty
}

bool SaveGridAction::ReadActionParameters()
{
	//pointers to input & output to interact with screen
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//receiving the file name from the user
	pOut->PrintMessage("Enter filename:   ");

	//using GetString() to recieve what the user types and concatenate .txt with it to make it a file
	filename = pIn->GetString(pOut) + ".txt";
	return true;
}

void SaveGridAction::Execute()
{
	//Calling the above function to get the filename
	ReadActionParameters();

	//get grid pointer
	Grid* pGrid = pManager->GetGrid();


	//creating a "output file stream" object to write on
	ofstream OutFile(filename);

	//check for file validity and creation
	if (OutFile.is_open())
	{
		pGrid->CountObjects();

		//This tells the grid to scan every cell & find all objects of required GameObjectType
		//then each object call its saveto write their cell number in outfile
		//They need to be ordered to follow the format required
		pGrid->SaveAll(OutFile, FLAG_TYPE);
		pGrid->SaveAll(OutFile, WATER_PIT_TYPE);
		pGrid->SaveAll(OutFile, DANGER_ZONE_TYPE);
		pGrid->SaveAll(OutFile, BELT_TYPE);
		pGrid->SaveAll(OutFile, WORKSHOP_TYPE);
		pGrid->SaveAll(OutFile, ANTENNA_TYPE);
		pGrid->SaveAll(OutFile, ROTATING_GEAR_TYPE);




		//closing file to save & free memory
		OutFile.close();

		Output* pOut = pGrid->GetOutput();

		pOut->PrintMessage("Grid saved successfully to" + filename + ". Click to continue");
	}
	else
		pManager->GetGrid()->PrintErrorMessage("Error: Unable to create file!");
}

SaveGridAction::~SaveGridAction()
{
}
