#include "Output.h"

#include "Input.h"
#include <random>

#include <iostream>
////////////////////////////////////////////////////////////////////////////////////////// 

Output::Output()
{
	// Initialize user interface parameters
	UI.InterfaceMode = MODE_DESIGN;

	// Widths and Heights

	UI.StatusBarHeight = 60;
	UI.CommandsBarHeight = 100;
	UI.CommandItemWidth = 70;
	UI.ToolBarHeight = 55;
	UI.MenuItemWidth = 55;

	UI.width = 1210; // make it divisible by NumHorizontalCells
	UI.height = 610; 
	UI.wx = 5;
	UI.wy = 5;

	UI.CellWidth = UI.width / NumHorizontalCells;
	UI.CellHeight = (UI.height -  UI.ToolBarHeight - UI.StatusBarHeight - UI.CommandsBarHeight) / NumVerticalCells;

	// Pen Colors of messages of status bar and players' info
	UI.MsgColor = GREEN;
	UI.PlayerInfoColor = DARKSLATEBLUE;

	// Background Colors of toolbar and statusbar 
	UI.ToolBarColor = color(100, 100, 100);
	UI.StatusBarColor = BLACK; 
	UI.CommandBarColor = UI.ToolBarColor;
	UI.BackgroundColor = color(50, 50, 50);

	// Line Colors of the borders of each cell
	UI.GridLineColor = color(45, 50, 60);

	// Cell Color if Empty & Cell Number Font & Color
	UI.CellColor = DARKGRAY;
	UI.CellNumFont = 13;
	UI.CellNumColor = WHITE;

	UI.CommandBarTextFont = 30;

	// Belt Line Width and Color
	UI.BeltLineWidth = 6;
	UI.BeltOutlineColor = BLACK;
	UI.BeltFillColor = DIMGRAY;
	UI.BeltTriangleColor = WHITE;

	UI.WaterPitsCellColor = DARKSLATEBLUE;
	UI.WaterWavesColor = LIGHTSLATEBLUE;
	UI.WaterBubblesColor = GHOSTWHITE;
	UI.DangerZoneCellColor = color(70, 70, 70);

	// The X and Y Offsets of the Space BEFORE Drawing the Belt (offset from the start X and Y of the Cell)
	UI.BeltXOffset = (UI.CellWidth - 2 * UI.BeltLineWidth) / 5;
	UI.BeltYOffset = (UI.CellHeight / 4) * 3;

	// Flag and Flag Pole Colors
	UI.FlagPoleWidth = 6;
	UI.FlagPoleHeight = UI.CellHeight / 1.5;
	UI.FlagWidth = UI.CellWidth / 4;
	UI.FlagHeight = UI.FlagPoleHeight / 2;

	UI.FlagColor = RED;
	UI.FlagPoleColor = GHOSTWHITE;
	UI.FlagPoleTopColor = GOLD;

	// Drop Shadow Color and Offset
	UI.DropShadowColor = BLACK;
	UI.DropShadowOffset = 3;

	// Commands X and Y Coordinates
	UI.SpaceBetweenCommandsSlots = 10;
	UI.AvailableCommandsXOffset = 10;
	UI.AvailableCommandsYOffset = -30;


	// Colors of the 2 Players
	UI.PlayerColors[0] = GOLD;
	UI.PlayerColors[1] = DARKSLATEBLUE;
	/*UI.PlayerColors[2] = KHAKI;
	UI.PlayerColors[3] = CHOCOLATE;*/

	UI.cellImageHeight = 55;
	UI.cellImageWidth = 55;

	// Create the output window
	pWind = CreateWind(UI.width + 15, UI.height, UI.wx, UI.wy); 

	// Change the title
	pWind->ChangeTitle("RoboRally");

	// Draw background
	pWind->SetBrush(UI.BackgroundColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.height, FILLED);

	// Create the toolbar, grid area and status bar
	CreateDesignModeToolBar();
	ClearGridArea();
	ClearStatusBar();
	ClearCommandsBar();

}

////////////////////////////////////////////////////////////////////////////////////////// 

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	// The Window Object is created inside the Ouput class
	window* pW = new window(w, h, x, y);
	return pW;
}

////////////////////////////////////////////////////////////////////////////////////////// 

Input* Output::CreateInput() const
{
	// The Input Object is created inside the Output class
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Some Utility Functions										//
//======================================================================================//

int Output::GetCellStartX(const CellPosition & cellPos) const
{
	///TODO: implement the following function as described in Output.h file
	
	if (cellPos.IsValidCell())
	{
		return cellPos.HCell() * UI.CellWidth;
	}
	else
	{
		return 0;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCellStartY(const CellPosition & cellPos) const
{
	///TODO: implement the following function as described in Output.h file
	
	if (cellPos.IsValidCell())
	{
		return cellPos.VCell() * UI.CellHeight + UI.ToolBarHeight;
	}
	else
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const
{
	// Clear by drawing a rectangle filled with toolbar background color
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	pWind->DrawImage("images\\Logo.jpg", UI.width - 97, 0, 97, 55);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawTriangle(int triangleCenterX, int triangleCenterY, int triangleHeight, int triangleWidth, Direction direction, color triangleColor, drawstyle style, int penWidth) const
{
	int x1, y1, x2, y2, x3, y3;

	///TODO: Calculate the coordiantes of the 3 vertices of the triangle based on the passed parameters

	switch (direction) {
		case UP:
			x1 = triangleCenterX - triangleWidth / 2;
			y1 = triangleCenterY + triangleHeight / 2;
			x2 = triangleCenterX + triangleWidth / 2;
			y2 = triangleCenterY + triangleHeight / 2;
			x3 = triangleCenterX;
			y3 = triangleCenterY - triangleHeight / 2;
			break;
		case DOWN:
			x1 = triangleCenterX - triangleWidth / 2;
			y1 = triangleCenterY - triangleHeight / 2;
			x2 = triangleCenterX + triangleWidth / 2;
			y2 = triangleCenterY - triangleHeight / 2;
			x3 = triangleCenterX;
			y3 = triangleCenterY + triangleHeight / 2;
			break;
		case LEFT:
			x1 = triangleCenterX + triangleHeight / 2;
			y1 = triangleCenterY - triangleWidth / 2;
			x2 = triangleCenterX + triangleHeight / 2;
			y2 = triangleCenterY + triangleWidth / 2;
			x3 = triangleCenterX - triangleHeight / 2;
			y3 = triangleCenterY;
			break;
		case RIGHT:
			x1 = triangleCenterX - triangleHeight / 2;
			y1 = triangleCenterY - triangleWidth / 2;
			x2 = triangleCenterX - triangleHeight / 2;
			y2 = triangleCenterY + triangleWidth / 2;
			x3 = triangleCenterX + triangleHeight / 2;
			y3 = triangleCenterY;
			break;
	}
	///TODO: Continue the implementation

	pWind->DrawTriangle(x1, y1, x2, y2, x3, y3, style);
	
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawImageInCell(const CellPosition& cellPos, string image, int width = UI.cellImageWidth, int height = UI.cellImageHeight) const
{
	// TODO: Validate the cell position
	if (!cellPos.IsValidCell())
		return;

	int x = GetCellStartX(cellPos) + UI.CellWidth / 4;
	int y = GetCellStartY(cellPos) + UI.CellHeight / 4;

	// TODO: Complete the implementation of this function
	try {
		pWind->DrawImage(image, x, y, width, height);
	} catch (...) {
		cout << "Error loading image: " << image << endl;
	}

}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::ClearStatusBar() const
{
	// Clear drawing a rectangle filled with statusbar background color
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

void Output::ClearCommandsBar() const
{
	// Clear drawing a rectangle filled with command bar background color
	pWind->SetPen(UI.CommandBarColor, 1);
	pWind->SetBrush(UI.CommandBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight - UI.CommandsBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearGridArea() const
{
	// Draw each cell in the Grid: ( NumVerticalCells * NumberHorizontalCells )
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			CellPosition cellPos(i, j);
			DrawCell(cellPos);
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDesignModeToolBar() const
{
	UI.InterfaceMode = MODE_DESIGN;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// ** MAKE SURE THAT THE IMAGES ARE .JPG FILES **
	string MenuItemImages[DESIGN_ITM_COUNT];
	MenuItemImages[ITM_EXIT] = "images\\Menu_Exit.jpg";
	MenuItemImages[ITM_SWITCH_TO_PLAY_MODE] = "images\\Menu_SwitchToGame.jpg";
	
	///TODO: Change the path of the images as needed
	MenuItemImages[ITM_SET_FLAG_CELL] = "images\\FlagIcon.jpg";
	MenuItemImages[ITM_ADD_ANTENNA] = "images\\AntennaIcon.jpg";
	MenuItemImages[ITM_ADD_BELT] = "images\\BeltIcon.jpg";
	MenuItemImages[ITM_ADD_WORKSHOP] = "images\\WorkshopIcon.jpg";
	MenuItemImages[ITM_ADD_WATER_PIT] = "images\\WaterPitIcon.jpg";
	MenuItemImages[ITM_ADD_DANGER_ZONE] = "images\\DangerIcon.jpg";
	MenuItemImages[ITM_ADD_ROTATING_GEAR_CLOCKWISE] = "images\\GearClockwiseIcon.jpg";
	MenuItemImages[ITM_ADD_ROTATING_GEAR_ANTICLOCKWISE] = "images\\GearAnticlockwiseIcon.jpg";
	MenuItemImages[ITM_COPY] = "images\\CopyIcon.jpg";
	MenuItemImages[ITM_CUT] = "images\\CutIcon.jpg";
	MenuItemImages[ITM_PASTE] = "images\\PasteIcon.jpg";
	MenuItemImages[ITM_DELETE] = "images\\DeleteIcon.jpg";
	MenuItemImages[ITM_SAVE] = "images\\SaveIcon.jpg";
	MenuItemImages[ITM_LOAD] = "images\\LoadIcon.jpg";
	
	///TODO: Prepare images for each menu item and add it to the list



	// Draw menu item one image at a time
	for(int i=0; i < DESIGN_ITM_COUNT; i++) {
		try {
			pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
			pWind->SetPen(BLACK, 1);
			pWind->DrawRectangle(i * UI.MenuItemWidth, 0, (i + 1) * UI.MenuItemWidth, UI.ToolBarHeight, FRAME);
		}
		catch (...) {
			cout << "Error loading image" << endl;
		}
		if (i == DESIGN_ITM_COUNT - 1) {
			// Draw a line after the last item to separate between the menu items and the grid
			pWind->SetPen(UI.GridLineColor, 3);
			pWind->DrawLine((i + 1) * UI.MenuItemWidth, 0, (i + 1) * UI.MenuItemWidth, UI.ToolBarHeight);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayModeToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// ** MAKE SURE THAT THE IMAGES ARE .JPG FILES **
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_SWITCH_TO_DESIGN_MODE] = "images\\Menu_SwitchToGrid.jpg";

	///TODO: Change the path of the images as needed
	MenuItemImages[ITM_EXECUTE_COMMANDS] = "images\\Menu_Dice.jpg";
	MenuItemImages[ITM_SELECT_COMMAND] = "images\\Menu_Dice.jpg";

	///TODO: Prepare images for each menu item and add it to the list



	// Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++) {
		try {
			pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
			pWind->SetPen(BLACK, 1);
			pWind->DrawRectangle(i * UI.MenuItemWidth, 0, (i + 1) * UI.MenuItemWidth, UI.ToolBarHeight, FRAME);
		}
		catch (...) {
			cout << "Error loading image" << endl;
		}
		if (i == PLAY_ITM_COUNT - 1) {
			// Draw a line after the last item to separate between the menu items and the grid
			pWind->SetPen(UI.GridLineColor, 3);
			pWind->DrawLine((i + 1) * UI.MenuItemWidth, 0, (i + 1) * UI.MenuItemWidth, UI.ToolBarHeight);
		}
	}
}

void Output::CreateCommandsBar(Command savedCommands[], int savedCommandsCount, Command availableCommands[], int availableCommandsCount) const
{
    ClearCommandsBar();
	UI.InterfaceMode = MODE_PLAY;
	string CommandItemImages[COMMANDS_COUNT];
	CommandItemImages[NO_COMMAND] = "images\\NoCommandCard.jpg";
	CommandItemImages[MOVE_FORWARD_ONE_STEP] = "images\\MoveForwardCard.jpg";
	CommandItemImages[MOVE_FORWARD_TWO_STEPS] = "images\\MoveForwardTwoCard.jpg";
	CommandItemImages[MOVE_FORWARD_THREE_STEPS] = "images\\MoveForwardThreeCard.jpg";
	CommandItemImages[MOVE_BACKWARD_ONE_STEP] = "images\\MoveBackwardCard.jpg";
	CommandItemImages[MOVE_BACKWARD_TWO_STEPS] = "images\\MoveBackwardTwoCard.jpg";
	CommandItemImages[MOVE_BACKWARD_THREE_STEPS] = "images\\MoveBackwardThreeCard.jpg";
	CommandItemImages[ROTATE_CLOCKWISE] = "images\\RotateRight.jpg";
	CommandItemImages[ROTATE_COUNTERCLOCKWISE] = "images\\RotateLeft.jpg";
	// TODO: Prepare images for more items with .jpg extensions and add them to the list 

	pWind->SetPen(BLACK, 4);
	pWind->DrawLine(UI.width / 2, UI.height - UI.StatusBarHeight - UI.CommandsBarHeight, UI.width / 2, UI.height - UI.StatusBarHeight);

	DrawCommands(availableCommands, availableCommandsCount, CommandItemImages, UI.AvailableCommandsXOffset + (UI.width / 2), UI.height - UI.StatusBarHeight - (UI.CommandsBarHeight / 2), "AVAILABLE", "COMMANDS");
	DrawCommands(savedCommands, savedCommandsCount, CommandItemImages, UI.AvailableCommandsXOffset, UI.height - UI.StatusBarHeight - (UI.CommandsBarHeight / 2), "SAVED", "COMMANDS");
    
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawOutlinedText(int x, int y, string text, color outlineColor, color textColor) const {
	pWind->SetPen(outlineColor);

	// ugly
	pWind->DrawString(x - 2, y, text);
	pWind->DrawString(x + 2, y, text);
	pWind->DrawString(x, y - 2, text);
	pWind->DrawString(x, y + 2, text);
	pWind->DrawString(x - 2, y - 2, text);
	pWind->DrawString(x + 2, y - 2, text);
	pWind->DrawString(x - 2, y + 2, text);
	pWind->DrawString(x + 2, y + 2, text);

	pWind->SetPen(textColor);

	pWind->DrawString(x, y, text);
}

void Output::DrawCommands(Command commands[], int commandsCount, string commandItemImages[], int startX, int startY, string word1, string word2) const
{
	if (UI.InterfaceMode == MODE_DESIGN)
		return;
	
	// Define the size and spacing for the available commands
	int availableCommandWidth = UI.CommandItemWidth / 2;
	int availableCommandHeight = UI.CommandsBarHeight / 2;


	int textWidth = 0, textHeight = 0;

	// Draw the "Available Commands" text above the command slots
	pWind->SetFont(UI.CommandBarTextFont, BOLD, BY_NAME, "Comic Sans MS");
	pWind->GetStringSize(textWidth, textHeight, word1);
	DrawOutlinedText(startX, startY - textHeight, word1, BLACK, WHITE);


	pWind->GetStringSize(textWidth, textHeight, word2);
	DrawOutlinedText(startX, startY, word2, BLACK, WHITE);

	for (int i = 0; i < commandsCount; ++i)
	{
		int x = startX + textWidth + i * (availableCommandWidth) + 10;
		int y = startY + UI.AvailableCommandsYOffset; // Adjust the Y position to be below the text
		

		// Draw the command slot (assuming you have an image for the available commands)
		pWind->DrawImage(commandItemImages[commands[i]], x, y, availableCommandWidth, availableCommandHeight);
		

		// Draw the command number below the card
		pWind->SetPen(UI.CellNumColor);
		pWind->SetFont(UI.CellNumFont, BOLD, BY_NAME, "Arial");
		int w = 0, h = 0;
		pWind->GetIntegerSize(w, h, i + 1);
		int numX = x + (availableCommandWidth - w) / 2;
		int numY = y + availableCommandHeight + 5; // Adjust the Y position to be below the card
		pWind->DrawInteger(numX, numY, i + 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	// Set pen and font before drawing the string on the window
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(18, BOLD , BY_NAME, "Verdana");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.3), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintPlayersInfo(string info)
{
	///TODO: Clear what was written on the toolbar
	CreatePlayModeToolBar();

	// One of the correct ways to implement the above TODO is to call CreatePlayModeToolBar(); 
	// to clear what was written in the player info (there are other ways too � You are free to use any)

	// Set the pen and font before drawing the string on the window
	pWind->SetPen(UI.PlayerInfoColor); 
	pWind->SetFont(20, BOLD , BY_NAME, "Verdana");   

	int w=0, h=0;

	///TODO: Calculate the Width and Height of the string if drawn using the current font 
	//       (Use GetStringSize() window function) and set the "w" and "h" variables with its width and height
	pWind->GetStringSize(w, h, info);


	// Set the start X & Y coordinate of drawing the string
	int x = UI.width - w - 20; // space 20 before the right-side of the window
	                           // ( - w ) because x is the coordinate of the start point of the string (upper left)
	int y = (UI.ToolBarHeight - h) / 2; // in the Middle of the toolbar height

	///TODO: Draw the string "info" in the specified location (x, y)

	pWind->DrawString(x, y, info);



}

void Output::FlushMouseQueue() const {
	pWind->FlushMouseQueue();
}

//======================================================================================//
//			         			Game Drawing Functions   								//
//======================================================================================//

void Output::DrawCell(const CellPosition & cellPos, color cellColor) const
{
	// Get the Cell Number (from 1 to NumVerticalCells*NumHorizontalCells) and the X & Y of its upper left corner
	int cellNum = cellPos.GetCellNum();
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// ----- 1- Draw the cell itself (background) --> Filled Rectangle -----
	pWind->SetPen(UI.GridLineColor, 1);
	
	pWind->SetBrush(cellColor);
	

	///TODO: Draw the Cell Rectangle using the appropriate coordinates
	//       using cellStartX, cellStartY, UI.CellWidth, UI.CellHeight
	pWind->DrawRectangle(cellStartX, cellStartY, cellStartX + UI.CellWidth, cellStartY + UI.CellHeight);

	DrawCellNum(cellPos);

	
}

void Output::DrawCellNum(const CellPosition& cellpos) const
{
	// ----- 2- Draw the CELL number (the small number at the bottom right of the cell) -----
	pWind->SetPen(UI.CellNumColor);
	pWind->SetFont(UI.CellNumFont, BOLD, BY_NAME, "Verdana");

	int w = 0, h = 0;

	int cellNum = cellpos.GetCellNum();
	int cellStartX = GetCellStartX(cellpos);
	int cellStartY = GetCellStartY(cellpos);

	///TODO: Get the Width and Height of the Cell Number if written using the current font 
	//       (Use GetIntegerSize() window function) and set the "w" and "h" variables with its width and height

	pWind->GetIntegerSize(w, h, cellNum);


	// Calculate X & Y coordinate of the start point of writing the card number (upper left point of the cell num)
	int x = cellStartX + (UI.CellWidth - w - 1);   // space 1 from the end of the cell width
	// ( - w ) because x is for the start point of cell num (num's left corner)
	int y = cellStartY + (UI.CellHeight - h - 1);  // space 1 from the end of the cell height
	// ( - w ) because y is for the start point of cell num (num's upper corner)

	///TODO: Draw the cell number in the x and y location

	pWind->DrawInteger(x, y, cellNum);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawPlayer(const CellPosition & cellPos, int playerNum, color playerColor, Direction direction) const
{
	// TODO: Validate the cell position and the playerNum, if not valid return

	if (cellPos.IsValidCell() == false || playerNum < 0 || playerNum >= MaxPlayerCount)
		return;
	

	// Get the X & Y coordinates of the start point of the cell (its upper left corner)
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// Calculate the Radius of the Player's Triangle
	int radius = UI.CellWidth / 8; // proportional to cell width

	// Calculate the horizontal space before drawing players triangles (space from the left border of the cell)
	int ySpace = UI.CellHeight / 6; // proportional to cell height

	// Note: Players' Triangles Locations depending on "playerNum" is as follows:
	// Player_0
	// Player_1

	// Calculate the Y coordinate of the center of the player's triangle (based on playerNum)
	int y = cellStartY + ySpace + radius + 2;
	if (playerNum == 1)
		y += 2 * (radius + 2); // because playerNum 1 is drawn in the second row of triangles

	// Calculate the X coordinate of the center of the player's triangle (based on playerNum)
	int x = cellStartX + UI.BeltXOffset + radius + 4; // UI.BeltXOffset is used to draw players' triangles 
														// AFTER the Belt start vertical line (assuming there is a belt)
														// for not overlapping with belts

	// TODO: Draw the player triangle in center(x,y) and filled with the playerColor passed to the function
	pWind->SetPen(BLACK);
	pWind->SetBrush(playerColor);
	DrawTriangle(x, y, radius, radius, direction, playerColor, FILLED);
	
}



//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawPill(int x1, int y1, int x2, int y2, int radius, Direction dir, drawstyle style) const 
{
	if (style == FILLED) {
		//pWind->DrawEllipse(x1 - radius, y1 - radius, x1 + radius, y1 + radius, FILLED);
		//pWind->DrawEllipse(x2 - radius, y2 - radius, x2 + radius, y2 + radius, FILLED);

		if (dir == RIGHT || dir == LEFT) {
			pWind->DrawRectangle(x1, y1 - radius, x2, y2 + radius, FILLED, 10, 10);
		}
		else {
			pWind->DrawRectangle(x1 - radius, y1, x2 + radius, y2, FILLED, 10, 10);
		}
	}
	else {
		if (dir == RIGHT || dir == LEFT) {
			pWind->DrawLine(x1, y1 - radius, x2, y2 - radius);
			pWind->DrawLine(x1, y1 + radius, x2, y2 + radius);
			pWind->DrawArc(x1 - radius, y1 - radius, x1 + radius, y1 + radius, 90, 270);
			pWind->DrawArc(x2 - radius, y2 - radius, x2 + radius, y2 + radius, 270, 90);
		}
		else {
			pWind->DrawLine(x1 - radius, y1, x2 - radius, y2);
			pWind->DrawLine(x1 + radius, y1, x2 + radius, y2);
			pWind->DrawArc(x1 - radius, y1 - radius, x1 + radius, y1 + radius, 180, 360);
			pWind->DrawArc(x2 - radius, y2 - radius, x2 + radius, y2 + radius, 0, 180);
		}
	}
}

void Output::DrawBelt(const CellPosition& fromCellPos, const CellPosition& toCellPos) const
{

	Direction triangleDir; // the direction of the triangle to be drawn at the center of the belt line (pointing to the direction of the belt)
	// TODO: Validate the fromCell and toCell (Must be Horizontal or Vertical, and we can't have the first cell as a starting cell for a belt)
	if (fromCellPos.IsValidCell() == false || toCellPos.IsValidCell() == false || fromCellPos.GetCellNum() == 1)
		return;
	else {
		if (fromCellPos.HCell() == toCellPos.HCell()) triangleDir = (fromCellPos.VCell() < toCellPos.VCell()) ? DOWN : UP;
		else if (fromCellPos.VCell() == toCellPos.VCell()) triangleDir = (fromCellPos.HCell() < toCellPos.HCell()) ? RIGHT : LEFT;
		else return; // not horizontal or vertical
	}


	// Get the start X and Y coordinates of the upper left corner of the fromCell and toCell
	int fromCellStartX = GetCellStartX(fromCellPos);
	int fromCellStartY = GetCellStartY(fromCellPos);
	int toCellStartX = GetCellStartX(toCellPos);
	int toCellStartY = GetCellStartY(toCellPos);
	
	int beltFromCellX;
	int beltToCellX;
	int beltFromCellY;
	int beltToCellY;

	switch (triangleDir) {
		case UP:
			beltFromCellX = fromCellStartX + UI.CellWidth / 2;
			beltFromCellY = fromCellStartY + UI.BeltYOffset;
			beltToCellX = toCellStartX + UI.CellWidth / 2;
			beltToCellY = toCellStartY + UI.CellHeight - UI.BeltYOffset;
			break;
		case DOWN:
			beltFromCellX = fromCellStartX + UI.CellWidth / 2;
			beltFromCellY = fromCellStartY + UI.CellHeight - UI.BeltYOffset;
			beltToCellX = toCellStartX + UI.CellWidth / 2;
			beltToCellY = toCellStartY + UI.BeltYOffset;
			break;
		case LEFT:
			beltFromCellX = fromCellStartX + UI.BeltYOffset;
			beltFromCellY = fromCellStartY + UI.CellHeight / 2;
			beltToCellX = toCellStartX + UI.CellWidth - UI.BeltYOffset;
			beltToCellY = toCellStartY + UI.CellHeight / 2;
			break;
		case RIGHT:
			beltFromCellX = fromCellStartX + UI.CellWidth - UI.BeltYOffset;
			beltFromCellY = fromCellStartY + UI.CellHeight / 2;
			beltToCellX = toCellStartX + UI.BeltYOffset;
			beltToCellY = toCellStartY + UI.CellHeight / 2;
			break;
	}

	// TODO: Draw the belt line and the triangle at the center of the line pointing to the direction of the belt

	// TODO: 1. Set pen color and width using the appropriate parameters of UI_Info object (UI)
	//       2. Draw the line of the belt using the appropriate coordinates

	int radius = 10;
	pWind->SetPen(UI.BeltOutlineColor, UI.BeltLineWidth);
	pWind->SetBrush(UI.BeltFillColor);
	DrawPill(beltFromCellX, beltFromCellY, beltToCellX, beltToCellY, radius, triangleDir, FILLED); // body

	// belt chevron pattern

	if (triangleDir == UP) {
		for (int i = beltFromCellY - 20; i >= beltToCellY; i -= 20) {
			pWind->DrawLine(beltFromCellX - UI.BeltLineWidth, i, beltToCellX + UI.BeltLineWidth, i);
		}
	} else if (triangleDir == DOWN) {
		for (int i = beltFromCellY + 20; i <= beltToCellY; i += 20) {
			pWind->DrawLine(beltFromCellX - UI.BeltLineWidth, i, beltToCellX + UI.BeltLineWidth, i);
		}
	} else if (triangleDir == LEFT) {
		for (int i = beltFromCellX - 20; i >= beltToCellX; i -= 20) {
			pWind->DrawLine(i, beltFromCellY - UI.BeltLineWidth, i, beltToCellY + UI.BeltLineWidth);
		}
	} else if (triangleDir == RIGHT) {
		for (int i = beltFromCellX + 20; i <= beltToCellX; i += 20) {
			pWind->DrawLine(i, beltFromCellY - UI.BeltLineWidth, i, beltToCellY + UI.BeltLineWidth);
		}
	}
	
	// TODO: Draw the triangle at the center of the belt line pointing to the direction of the belt
	int triangleWidth = UI.CellWidth / 4;
	int triangleHeight = UI.CellHeight / 4;

	int triangleCenterX = triangleDir == RIGHT || triangleDir == LEFT ? (beltFromCellX + beltToCellX) / 2 : beltFromCellX;
	int triangleCenterY = triangleDir == UP || triangleDir == DOWN ? (beltFromCellY + beltToCellY) / 2 : beltFromCellY;

	pWind->SetPen(UI.BeltOutlineColor);
	pWind->SetBrush(UI.BeltTriangleColor);
	DrawTriangle(triangleCenterX, triangleCenterY, triangleHeight, triangleWidth, triangleDir, UI.CommandBarColor, FILLED);



}

//////////////////////////////////////////////////////////////////////////////////////////


void Output::DrawFlag(const CellPosition& cellPos) const
{
	// TODO: Validate the cell position
	if (cellPos.IsValidCell() == false)
		return;

	// Get the X and Y coordinates of the start point of the cell (its upper left corner)
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// TODO: Draw the flag as a line with a triangle connected to it directed to right

	// TODO: 1. Draw the flag pole (the line)
	int flagPoleStartX = cellStartX + UI.CellWidth / 2.3;
	int flagPoleStartY = cellStartY + UI.CellHeight / 5;

	pWind->SetPen(UI.DropShadowColor, 3);
	pWind->SetBrush(UI.DropShadowColor);
	pWind->DrawLine(flagPoleStartX + UI.DropShadowOffset, flagPoleStartY + UI.DropShadowOffset, flagPoleStartX + UI.DropShadowOffset, flagPoleStartY + UI.FlagPoleHeight + UI.DropShadowOffset);

	int triangleCenterX = flagPoleStartX + UI.FlagWidth / 2.5;
	int triangleCenterY = flagPoleStartY + UI.FlagHeight / 2 - 3;

	pWind->SetPen(UI.DropShadowColor, 2);
	pWind->SetBrush(UI.DropShadowColor);
	DrawTriangle(triangleCenterX + UI.DropShadowOffset, triangleCenterY + UI.DropShadowOffset, UI.FlagHeight, UI.FlagWidth, RIGHT, UI.FlagColor, FILLED);

	pWind->SetPen(UI.FlagPoleColor, UI.FlagPoleWidth);
	pWind->DrawLine(flagPoleStartX, flagPoleStartY, flagPoleStartX, flagPoleStartY + UI.FlagPoleHeight);

	// 		 2. Draw the flag (the triangle)

	pWind->SetPen(BLACK);
	pWind->SetBrush(UI.FlagColor);
	DrawTriangle(triangleCenterX, triangleCenterY, UI.FlagHeight, UI.FlagWidth, RIGHT, UI.FlagColor, FILLED);

	pWind->SetPen(UI.FlagPoleTopColor);
	pWind->SetBrush(UI.FlagPoleTopColor);
	pWind->DrawCircle(flagPoleStartX, flagPoleStartY, 4, FILLED);

	//pWind->SetPen(BLACK);
	//pWind->DrawLine(flagPoleStartX - 10, flagPoleStartY + UI.FlagPoleHeight, flagPoleStartX + 10, flagPoleStartY + UI.FlagPoleHeight, FRAME);
	//
}

void Output::DrawRotatingGear(const CellPosition& cellPos, bool clockwise) const
{
	// TODO: Validate the cell position
	if (cellPos.IsValidCell() == false)
		return;
	
	// TODO: Draw the rotating gear image in the cell based on the passed direction (clockwise or counter clockwise)
	string gearImage;
	if (clockwise)
	{
		gearImage = "images\\Gear_CW.jpg";
	}
	else
	{
		gearImage = "images\\Gear_CCW.jpg";
	}

	DrawImageInCell(cellPos, gearImage);


}

void Output::DrawAntenna(const CellPosition& cellPos) const
{
	// TODO: Validate the cell position
	if (cellPos.IsValidCell() == false)
		return;


	// TODO: Draw the antenna image in the cell
	DrawImageInCell(cellPos, "images\\Antenna.jpg");

	
	
}

void Output::DrawWorkshop(const CellPosition& cellPos) const
{
	// TODO: Validate the cell position
	if (cellPos.IsValidCell() == false)
		return;

	// TODO: Draw the workshop image in the cell
	DrawImageInCell(cellPos, "images\\Workshop.jpg");
	


}

// Helper function for DrawDangerZone
color Output::DarkenColor(color original, int subtractAmount) const {
	int r = original.ucRed - subtractAmount;
	int g = original.ucGreen - subtractAmount;
	int b = original.ucBlue - subtractAmount;

	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;

	return color(r, g, b);
}

void Output::DrawDangerZone(const CellPosition& cellPos) const
{
    ///TODO: Complete the implementation of the following function
	if (cellPos.IsValidCell() == false || cellPos.GetCellNum() == 1)
		return;
	int x1 = GetCellStartX(cellPos);
	int y1 = GetCellStartY(cellPos);

	int x2 = x1 + UI.CellWidth;
	int y2 = y1 + UI.CellHeight;

	pWind->SetPen(RED, 1);
	pWind->SetBrush(UI.DangerZoneCellColor);
	pWind->DrawRectangle(x1, y1, x2, y2, FILLED);

	color darkerColor = UI.DangerZoneCellColor;
	for (int i = 1; i <= 40; i += 2) {
		darkerColor = DarkenColor(darkerColor, 4);
		pWind->SetPen(darkerColor, 1);
		pWind->SetBrush(darkerColor);
		pWind->DrawRectangle(x1 + i, y1 + i, x2 - i, y2 - i, FILLED);
	}

	DrawCellNum(cellPos);
	
}


void Output::DrawWaterPit(const CellPosition & cellPos) const
{
	if (cellPos.IsValidCell() == false || cellPos.GetCellNum() == 1)
		return;

	int x1 = GetCellStartX(cellPos);
	int y1 = GetCellStartY(cellPos);
	int x2 = x1 + UI.CellWidth;
	int y2 = y1 + UI.CellHeight;

	pWind->SetPen(UI.GridLineColor, 1);
	pWind->SetBrush(UI.WaterPitsCellColor);
	pWind->DrawRectangle(x1, y1, x2, y2, FILLED);

	pWind->SetPen(UI.WaterWavesColor, 2);
	pWind->SetBrush(UI.WaterWavesColor);
	int waveStartY = y1 + UI.CellHeight / 2;
	pWind->DrawRectangle(x1, waveStartY, x2, y2);
	pWind->DrawArc(x1, waveStartY + 10, x1 + UI.CellWidth/2, waveStartY - 10, 0, 180, FILLED);
	pWind->SetPen(UI.WaterPitsCellColor, 1);
	pWind->SetBrush(UI.WaterPitsCellColor);
	pWind->DrawArc(x1 + UI.CellWidth / 2, waveStartY - 10, x2, waveStartY + 10, 180, 360, FILLED);

	int numBubbles = 10;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> yPos(y1 + 10, waveStartY - 20);
	uniform_int_distribution<> xPos(x1 + 5, x2 - 5);
	for (int i = 1; i < 4; ++i) {
		int bubbleX = xPos(gen);
		int bubbleY = yPos(gen); // alternate bubble heights
		pWind->SetPen(UI.WaterBubblesColor, 2);
		pWind->SetBrush(UI.WaterPitsCellColor);
		pWind->DrawCircle(bubbleX, bubbleY, 6, FRAME);
	}

	pWind->SetPen(UI.GridLineColor, 1);
	pWind->DrawRectangle(x1, y1, x2, y2, FRAME);

	DrawCellNum(cellPos);
}

	
Output::~Output()
{
	// deallocating the window object
	delete pWind;
}

