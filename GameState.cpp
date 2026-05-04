#include "GameState.h"
#include "CellPosition.h"
#include "Grid.h"
#include "Player.h"
#include "Cell.h"
#include "Output.h"
#include <iostream>

GameState::GameState(Grid* pGrid)
{
	// Create all Player objects starting at the board's designated start cell.
	// The Grid provides the start cell position; the GameState owns the Player objects.
	Cell* startCell = pGrid->GetStartCell();
	Output* pOut = pGrid->GetOutput();

	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(startCell, i);
		PlayerList[i]->Draw(pOut); // draw initial position
	}

	currPlayerNumber = 0;         // Player 0 goes first by default
	currentPhase = PHASE_MOVEMENT;
	endGame = false;
}

GameState::~GameState()
{
	for (int i = 0; i < MaxPlayerCount; i++)
		delete PlayerList[i];
}

// ========== Player Access ==========

Player* GameState::GetCurrentPlayer() const
{
	///TODO: Return the player whose turn it is
	return PlayerList[currPlayerNumber];
}

Player* GameState::GetPlayer(int playerNum) const
{
	///TODO: Return the player with the given player number
	return PlayerList[playerNum];
}

void GameState::ResetAllPlayers(Grid* pGrid) {
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		Player*& currentPlayer = PlayerList[i];

		// Reset position to start cell
		Cell* startCell = pGrid->GetStartCell();


		delete currentPlayer;
		currentPlayer = new Player(startCell, i);
	}
}

// ========== Turn Management ==========

void GameState::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount;
	PlayerList[currPlayerNumber]->RandomizeAvailableCommands();
	
}

void GameState::SetFirstPlayer(int playerNum)
{
	///TODO: Implement this function to set which player goes first this round
	currPlayerNumber = playerNum;
}

// ========== Phase Management ==========

PhaseType GameState::GetCurrentPhase() const
{
	return currentPhase;
}

void GameState::SetCurrentPhase(PhaseType phase)
{
	currentPhase = phase;
}

void GameState::AdvancePhase()
{
	// Currently only PHASE_MOVEMENT exists.
	// [OPTIONAL BONUS] If you add PHASE_SHOOTING to the PhaseType enum (DEFS.h),
	// update this to cycle:  MOVEMENT --> SHOOTING --> MOVEMENT
	currentPhase = static_cast<PhaseType>(currentPhase+1 % 2);
	cout << currentPhase;
}

Player* GameState::FindShotPlayer(Player* shootingPlayer) const {
	int otherPlayerIndex = (shootingPlayer->GetPlayerNum() + 1) % MaxPlayerCount;
	Player* otherPlayer = GetPlayer(otherPlayerIndex);
	switch (shootingPlayer->GetDirection()) {
		case UP:
			if (shootingPlayer->GetCell()->GetCellPosition().HCell() != otherPlayer->GetCell()->GetCellPosition().HCell())
				break;
			for (int i = shootingPlayer->GetCell()->GetCellPosition().VCell(); i >= 0; i--) {
				if (i == otherPlayer->GetCell()->GetCellPosition().VCell()) return otherPlayer;
			}
			break;

		case DOWN:
			if (shootingPlayer->GetCell()->GetCellPosition().HCell() != otherPlayer->GetCell()->GetCellPosition().HCell())
				break;
			for (int i = shootingPlayer->GetCell()->GetCellPosition().VCell(); i < NumVerticalCells; i++) {
				if (i == otherPlayer->GetCell()->GetCellPosition().VCell()) return otherPlayer;
			}
			break;

		case LEFT:
			if (shootingPlayer->GetCell()->GetCellPosition().VCell() != otherPlayer->GetCell()->GetCellPosition().VCell())
				break;
			for (int i = shootingPlayer->GetCell()->GetCellPosition().HCell(); i >= 0; i--) {
				if (i == otherPlayer->GetCell()->GetCellPosition().HCell()) return otherPlayer;
			}
			break;

		case RIGHT:
			if (shootingPlayer->GetCell()->GetCellPosition().VCell() != otherPlayer->GetCell()->GetCellPosition().VCell())
				break;
			for (int i = shootingPlayer->GetCell()->GetCellPosition().HCell(); i < NumHorizontalCells; i++) {
				if (i == otherPlayer->GetCell()->GetCellPosition().HCell()) return otherPlayer;
			}
			break;
		default:
			return nullptr;
	}

	return nullptr;
}


// ========== End-Game ==========

bool GameState::GetEndGame() const
{
	return endGame;
}

void GameState::SetEndGame(bool end)
{
	endGame = end;
}

// ========== Drawing Helpers ==========

void GameState::DrawAllPlayers(Output* pOut) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
		PlayerList[i]->Draw(pOut);
}

void GameState::AppendPlayersInfo(string& info) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->AppendPlayerInfo(info);
		if (i < MaxPlayerCount - 1)
			info += ", ";
	}
	info += " | Curr = " + to_string(currPlayerNumber);
}

