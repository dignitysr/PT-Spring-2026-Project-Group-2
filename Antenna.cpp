#include "Antenna.h"





Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click

	// 2- Determine turn order based on each player's distance from the antenna.
	//    Hint: distance = |dV| + |dH|
	//    The player closest to the antenna plays first. Ties are broken by player number.
	//    Use pState to update the turn order accordingly.
	// 3- Print a message indicating which player will play first
	pOut->PrintMessage("The antenna will decide the turn of players. Click to continue ...");

	int player1Distance = abs(pState->GetPlayer1()->GetCellPosition().GetVCell() - antennaPosition.GetVCell()) +
		abs(pState->GetPlayer1()->GetCellPosition().GetHCell() - antennaPosition.GetHCell());

	int player2Distance = abs(pState->GetPlayer2()->GetCellPosition().GetVCell() - antennaPosition.GetVCell()) +
		abs(pState->GetPlayer2()->GetCellPosition().GetHCell() - antennaPosition.GetHCell());

	if (player1Distance < player2Distance) {
		pState->SetCurrentPlayer(1);
		pOut->PrintMessage("Player 1 will play first.");
	}
	else if (player2Distance < player1Distance) {
		pState->SetCurrentPlayer(2);
		pOut->PrintMessage("Player 2 will play first.");
	}
	else {
		if (pState->GetCurrentPlayer() == 1) {
			pState->SetCurrentPlayer(2);
			pOut->PrintMessage("Player 2 will play first.");
		}
		else {
			pState->SetCurrentPlayer(1);
			pOut->PrintMessage("Player 1 will play first.");
		}
	}

	pOut->ClearStatusBar();
}


Antenna::~Antenna()
{
}
