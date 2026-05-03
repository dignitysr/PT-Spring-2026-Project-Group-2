#include "CellPosition.h"
#include "UI_Info.h"
#include <iostream>

ostream& operator<<(ostream& out, const CellPosition& cellPos)
{
	out << "(" << cellPos.VCell() << ", " << cellPos.HCell() << ")";
	return out;
}

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	if (v <= NumVerticalCells - 1 && v >= 0)
	{
		vCell = v;
		return true;
	}
	else
	{
		return false;
	}

	///TODO: Implement this function as described in the .h file (don't forget the validation)

	 // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h) 
{
	if (h <= NumHorizontalCells-1&& h >= 0)
	{
		hCell = h;
		return true;
	}
	else
	{
		return false;
	}
	///TODO: Implement this function as described in the .h file (don't forget the validation)

  // this line sould be changed with your implementation
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	if (vCell >= 0 && vCell <= NumVerticalCells - 1 && hCell >= 0 && hCell <= NumHorizontalCells - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	///TODO: Implement this function as described in the .h file

     // this line sould be changed with your implementation
}

bool CellPosition::operator==(const CellPosition& other) {
	return GetCellNum() == other.GetCellNum();
}


int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	int v = cellPosition.VCell();
	int h = cellPosition.HCell();
	if (v < 0 || h < 0)
	{
		return -1;
	}
	int rowsfrombottom = (NumVerticalCells - 1 - v);
	int cellnum = (rowsfrombottom * NumHorizontalCells) + h + 1;
    return cellnum;

	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file

	 // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	if (cellNum >= 1 && cellNum <= (NumVerticalCells * NumHorizontalCells))
	{
		int h = (cellNum - 1) % NumHorizontalCells;
		int v = (NumVerticalCells - 1) - ((cellNum - 1) / NumHorizontalCells);
		position.SetVCell(v);
		position.SetHCell(h);
	}
	else return CellPosition(-1, -1); // return an invalid cell position if the passed cellNum is not valid

	/// TODO: Implement this function as described in the .h file

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum, Direction direction)
	{

		switch (direction)
		{
		case UP:
			SetVCell(vCell - addedNum);
			break;
		case DOWN:
			SetVCell(vCell + addedNum);
			break;
		case RIGHT:
			SetHCell(hCell + addedNum);
			break;
		case LEFT:
			SetHCell(hCell - addedNum);
			break;
		}

	}