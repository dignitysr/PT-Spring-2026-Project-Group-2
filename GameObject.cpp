#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

void GameObject::SetPosition(const CellPosition newPos, Grid* pGrid) {
	if (newPos.IsValidCell()) position = newPos;
}

GameObject::~GameObject()
{
}