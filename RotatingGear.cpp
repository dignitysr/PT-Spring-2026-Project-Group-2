#include "RotatingGear.h"
#include "Player.h"
#include "Output.h"




RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}

void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	//start of addition(Abdallah)
	if (!pPlayer) return;

	// 1- Print a message and change the message according to direction of rotation "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	string DirectionMessage = isClockWise ? "clockwise" : "/ anti-clockwise";
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("You have reached a rotating gear, you will rotate" + DirectionMessage + "Click to continue ...");
	

	// Waiting for a mouse click on the grid for acknowledgment
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);


	//2- Apply the roating gear's effect by rotating the player according to the direction
	
	//first we get el initial direction for the player
	Direction currentDirection;
	currentDirection = pPlayer->GetDirection();
	Direction nextDirection;

	//check if its clockwise seq:(up->right->down->left->up)
	if (isClockWise)
	{
		switch(currentDirection)
		{
		case UP:    nextDirection = RIGHT; break;
		case RIGHT: nextDirection = DOWN;  break;
		case DOWN:  nextDirection = LEFT;  break;
		case LEFT:  nextDirection = UP;    break;
		}
	}
	//it is anticlockwise seq:(up->left->down->right->up)
	else
	{
		switch (currentDirection)
		{
		case UP:    nextDirection = LEFT;  break;
		case LEFT:  nextDirection = DOWN;  break;
		case DOWN:  nextDirection = RIGHT; break;
		case RIGHT: nextDirection = UP;    break;
		}
	}
	//updating direction after rotation
	pPlayer->SetDirection(nextDirection);

	//end of addition
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}

void RotatingGear::Save(ofstream& OutFile, GameObjectType type)
{
	//Format:cell direction (1 for CW, 0 for ACW)
	OutFile << position.GetCellNum() << " " << (isClockWise ? 1 : 0) << endl;
}

RotatingGear::~RotatingGear()
{
}
