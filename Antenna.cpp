#include "Antenna.h"
#include "Player.h"
#include "GameState.h"
#include <cmath>



Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	pGrid->GetOutput()->PrintMessage("the antenna will decide the turn of players. Click to continue ... "); //print the massege
	int x, y;
	pGrid->GetInput()->GetPointClicked(x,y); //waiting for the  mouse click
	
	int antenaHcellpos = this->GetPosition().HCell(); // getting the h position of the antena
	int antenaVcellpos= this->GetPosition().VCell(); // getting the v position of the antena

	Player* p0 = pState->GetPlayer(0); //pointer for first player
	Player* p1 = pState->GetPlayer(1);//pointer for second player

	// getting the h and v position of the players
	int p0Hcellpos = p0->GetCell()->GetCellPosition().HCell();
		int p0Vcellpos= p0->GetCell()->GetCellPosition().VCell();
		int p1Hcellpos= p1->GetCell()->GetCellPosition().HCell();
		int p1Vcellpos= p1->GetCell()->GetCellPosition().VCell();

		// distance of player one and two
		int dist0 = abs(p0Hcellpos - antenaHcellpos) + abs(p0Vcellpos - antenaVcellpos);
		int dist1 = abs(p1Hcellpos - antenaHcellpos) + abs(p1Vcellpos - antenaVcellpos);

		int firstPlayerNum;
		if (dist0 <= dist1) // comparing dist of players in refrence to antena
		{
			firstPlayerNum=0;
			pGrid->GetOutput()->PrintMessage("player 0 will play first !");
			pGrid->GetInput()->GetCellClicked();
			pGrid->GetOutput()->ClearStatusBar();
		}
		else
		{
			firstPlayerNum=1;
			pGrid->GetOutput()->PrintMessage("player 1 will play first !");
			pGrid->GetInput()->GetCellClicked();
			pGrid->GetOutput()->ClearStatusBar();
		}
		pState->SetFirstPlayer(firstPlayerNum); // set the player who will play frist

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click

	// 2- Determine turn order based on each player's distance from the antenna.
	//    Hint: distance = |dV| + |dH|
	//    The player closest to the antenna plays first. Ties are broken by player number.
	//    Use pState to update the turn order accordingly.
	// 3- Print a message indicating which player will play first
}

void Antenna::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:cell
	if (type == ANTENNA_TYPE) 
	OutFile << position.GetCellNum() << endl;
}

bool Antenna::IsType(GameObjectType type) const { return type == ANTENNA_TYPE; }

void Antenna::Load(ifstream& InFile)
{
	int cellNum;
	if (InFile >> cellNum) // Read the cell number from the file
	{
		// Update the position using the helper function
		this->position = CellPosition::GetCellPositionFromNum(cellNum);
	}
}

Antenna* Antenna::Clone() const
{
	return new Antenna(*this);
}



Antenna::~Antenna()
{
}
