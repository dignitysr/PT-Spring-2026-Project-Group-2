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
	const string user = getenv("USERNAME");

	//using GetString() to recieve what the user types and concatenate .txt with it to make it a file
	filename = pIn->GetString(pOut) + ".txt";
	return true;
}

void SaveGridAction::Execute()
{
	//Calling the Function to get the filename
	ReadActionParameters();

	//get grid pointer
	Grid* pGrid = pManager->GetGrid();


	//creating a "output file stream" object to write on
	ofstream OutFile(filename);

	//check for file validity and creation
	if (OutFile.is_open())
	{
		pGrid->CountObjects();

		//This Action tells the Grid to save itself (polymorphism used)
		//tell the grid to save and loop throughout all cells and call save()
		pGrid->SaveAll(OutFile, FLAG_TYPE);
		cout << "flag type: " << FLAG_TYPE << endl;
		pGrid->SaveAll(OutFile, WATER_PIT_TYPE);
		cout << "water pit type: " << WATER_PIT_TYPE << endl;
		pGrid->SaveAll(OutFile, DANGER_ZONE_TYPE);
		cout << "danger zone type: " << DANGER_ZONE_TYPE << endl;
		pGrid->SaveAll(OutFile, BELT_TYPE);
		cout << "belt type: " << BELT_TYPE << endl;
		pGrid->SaveAll(OutFile, WORKSHOP_TYPE);
		cout << "workshop type: " << WORKSHOP_TYPE << endl;
		pGrid->SaveAll(OutFile, ANTENNA_TYPE);
		cout << "antenna type: " << ANTENNA_TYPE << endl;
		pGrid->SaveAll(OutFile, ROTATING_GEAR_TYPE);
		cout << "rotating gear type: " << ROTATING_GEAR_TYPE << endl;

		//for (int i = 0; i < NUM_OBJECT_TYPES; i++) {
		//	GameObjectType type = static_cast<GameObjectType>(i);
		//	pGrid->SaveAll(OutFile, type);
		//}


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
