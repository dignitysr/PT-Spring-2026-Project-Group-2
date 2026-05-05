#include "RotatingGear.h"
#include "Player.h"
#include "Output.h"


//start of addition(Abdallah)

//gearposition is passed to gameobject class using inheritance
RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;//intializing
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);//draw gear using el output class in specific correct position and arrow of rotation
}

void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	if (!pPlayer) return;//make sure there is a player

	//Print a message and change the message according to direction of rotation "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	string DirectionMessage = isClockWise ? "clockwise" : "/ anti-clockwise";
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("You have reached a rotating gear, you will rotate" + DirectionMessage + "Click to continue ...");//displays the direction message to ask the user which rotation direction he seeks
	

	// Waiting for a mouse click on the grid for acknowledgment
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);


	//Apply the roating gear's effect by rotating the player according to the direction
	
	//first we get el initial direction of el robot
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

	
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise; //rotation direction getter
}

void RotatingGear::Save(ofstream& OutFile, GameObjectType type)
{
	//writes cell index and 1 if clockwise and 0 if anticlockwise
	if (type == ROTATING_GEAR_TYPE)
	OutFile << position.GetCellNum() << " " << (isClockWise ? 1 : 0) << endl;
}
bool RotatingGear::IsType(GameObjectType type) const { return type == ROTATING_GEAR_TYPE; }

void RotatingGear::Load(ifstream& InFile) {
	int cellNum, direction;
	InFile >> cellNum >> direction; // Reads cellnum and direction -> 1/0

	this->position = CellPosition::GetCellPositionFromNum(cellNum);//reconstructs the row/coloumn coord men el cell num

	//convert integer (1) into bool
	this->isClockWise = (direction == 1);
}

RotatingGear* RotatingGear::Clone() const //used in copy & paste
{
	return new RotatingGear(*this);
}

RotatingGear::~RotatingGear() //deallocate any dynamic arr as usual
{
}
//end of addition