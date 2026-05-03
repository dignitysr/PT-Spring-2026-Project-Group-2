#include "LoadGridAction.h"

#include "Grid.h"
#include "Input.h"
#include "Output.h"
//All GameObjects
#include "Flag.h"
#include "WaterPit.h"
#include "DangerZone.h"
#include "Belt.h"
#include "Workshop.h"
#include "Antenna.h"
#include "RotatingGear.h"
#include <fstream>

LoadGridAction::LoadGridAction(ApplicationManager* pApp) :Action(pApp)
{
	//will remain empty
}

bool LoadGridAction::ReadActionParameters()
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

void LoadGridAction::Execute()
{
	//Calling the Function to get the filename
	ReadActionParameters();

	ifstream InFile(filename);

	if (!InFile.is_open())
	{
		pManager->GetGrid()->PrintErrorMessage("Error: File not found! Click to continue...");
		return;
	}
	Grid* pGrid = pManager->GetGrid();

	//clearing the grid before loading new data
	for (int r = 0; r < 10; r++) {      // NumVerticalCells
		for (int c = 0; c < 11; c++) {  // NumHorizontalCells
			// Note: You can't access pCellList directly if it's private in Grid!
			// You would have to do something like this:
			GameObject* pObj = pGrid->GetCell(CellPosition(r, c))->GetGameObject();
			if (pObj) {
				delete pObj;
				CellPosition pos(r, c);
				pGrid->RemoveObjectFromCell(pos); // You'd need this helper
			}
		}
	}

	int count;
	CellPosition tempPos(1, 1);
	


	// 1. Flags
	InFile >> count;
	for (int i = 0; i < count; i++) {
		Flag* pFlag = new Flag(tempPos);
		pFlag->Load(InFile);           // Flag reads its cell number
		pGrid->AddObjectToCell(pFlag);
	}

	// 2. Water Pits
	InFile >> count;
	for (int i = 0; i < count; i++) {
		WaterPit* pWP = new WaterPit(tempPos);
		pWP->Load(InFile);            // WaterPit reads its cell number
		pGrid->AddObjectToCell(pWP);
	}

	// 3. Danger Zones
	InFile >> count;
	for (int i = 0; i < count; i++) {
		DangerZone* pDZ = new DangerZone(tempPos);
		pDZ->Load(InFile);            // DangerZone reads its cell number
		pGrid->AddObjectToCell(pDZ);
	}

	// 4. Belts
	InFile >> count;
	for (int i = 0; i < count; i++) {
		// Belt constructor requires two positions; dummy values are overwritten in Load()
		Belt* pBelt = new Belt(tempPos, tempPos);
		pBelt->Load(InFile);          // Belt reads start_cell and end_cell
		pGrid->AddObjectToCell(pBelt);
	}

	// 5. Workshops
	InFile >> count;
	for (int i = 0; i < count; i++) {
		Workshop* pWS = new Workshop(tempPos);
		pWS->Load(InFile);            // Workshop reads its cell number
		pGrid->AddObjectToCell(pWS);
	}

	// 6. Antennas
	InFile >> count;
	for (int i = 0; i < count; i++) {
		Antenna* pAnt = new Antenna(tempPos);
		pAnt->Load(InFile);           // Antenna reads its cell number
		pGrid->AddObjectToCell(pAnt);
	}

	// 7. Rotating Gears
	InFile >> count;
	for (int i = 0; i < count; i++) {
		RotatingGear* pRG = new RotatingGear(tempPos, true);
		pRG->Load(InFile);           // RotatingGear reads cell and rotation_direction
		pGrid->AddObjectToCell(pRG);
	}

	InFile.close();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Grid Loaded successfully! Click to continue...");
}

LoadGridAction::~LoadGridAction()
{
}
