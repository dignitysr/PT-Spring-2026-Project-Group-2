#include "Input.h"

#include "Output.h"

#include "DEFS.h"

#include <iostream>
//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW) 
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if(Key == 13 )	// ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output *pO) const 
{

	///TODO: implement the GetInteger function as described in Input.h file 
	//       using function GetString() defined above and function stoi()
	
	//start of additions//
	//Clearing the status bar and preparing for input
	pO->PrintMessage("Please enter an integer: ");

	string Label = "";
	char key;

	//Loop to capture the entered characters until "Enter" is pressed
	while (true)
	{
		//waiting for a keyboard press
		pWind->WaitKeyPress(key);

		if (key == 13) {
			if (Label == "") {
				return 0;//Returning 0 if nothing is entered
			}
			break;
		}

		else if (key == 8) {
			if (Label.length() > 0) //ensuring the string is not already empty
			{
				Label.erase(Label.length() - 1);//identifies the index of the last character and erases it
			}
		}
		else if (key >= '0' && key <= '9') {
			Label += key;//string concatenation
		}
		//Updating the status bar so the user sees what they are typing
		pO->PrintMessage("Please enter an integer: " + Label);

	}

	// Note: stoi(s) converts string s into its equivalent integer (for example, "55" is converted to 55)

	return stoi(Label); //converting the final string to an integer & returning it
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{	
	int x = -1, y = -1;
	GetPointClicked(x, y); 

	//  ============ GUI in the Design mode ============
	if ( UI.InterfaceMode == MODE_DESIGN )	
	{
		// [1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int clickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (clickedItemOrder)
			{
			case ITM_SET_FLAG_CELL: return SET_FLAG_CELL;
			case ITM_EXIT: return EXIT;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;

				///TODO: Add cases for the other items of Design Mode
				//start of adjustments
			case ITM_ADD_ANTENNA: return ADD_ANTENNA;
			case ITM_ADD_BELT: return ADD_BELT;
			case ITM_ADD_WATER_PIT: return ADD_WATER_PIT;
			case ITM_ADD_DANGER_ZONE: return ADD_DANGER_ZONE;
			case ITM_ADD_WORKSHOP:  return ADD_WORKSHOP;
			case ITM_ADD_ROTATING_GEAR_CLOCKWISE: return ADD_ROTATING_GEAR_CLOCKWISE;
			case ITM_ADD_ROTATING_GEAR_ANTICLOCKWISE: return ADD_ROTATING_GEAR_ANTICLOCKWISE;
			case ITM_COPY: return COPY_OBJECT;
			case ITM_CUT: return CUT_OBJECT;
			case ITM_PASTE: return PASTE_OBJECT;
			case ITM_DELETE: return DELETE_OBJECT;
			case ITM_SAVE: return SAVE_GRID;
			case ITM_LOAD: return LOAD_GRID;
			//end of adjustments & all of the above was adding Items needed for design mode

			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ( (y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight - UI.CommandsBarHeight))
		{
			return GRID_AREA;	
		}

		if ((y >= UI.height - UI.StatusBarHeight - UI.CommandsBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return COMMAND;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		///TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType
		//start of adjustments(Abdallah)
		if (y >= 0 && y <= UI.ToolBarHeight) {
			int clickedItemOrder = (x / UI.MenuItemWidth);

			switch (clickedItemOrder)
			{
			case ITM_EXECUTE_COMMANDS: return EXECUTE_COMMANDS;
			case ITM_SELECT_COMMAND: return SELECT_COMMAND;
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;
			case ITM_REBOOT_REPAIR: return REBOOT_REPAIR;
			case ITM_NEW_GAME: return NEW_GAME;
			case ITM_EXIT_PLAY: return EXIT;

			default: return EMPTY;	// A click on empty place in toolbar
			}
		}
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight - UI.CommandsBarHeight))
		{
			return GRID_AREA;
		}

		if ((y >= UI.height - UI.StatusBarHeight - UI.CommandsBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return COMMAND;
		}

		// [3] User clicks on the status bar
		return STATUS;

	}

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if ( UI.InterfaceMode == MODE_DESIGN )	
	{
		if ( y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight - UI.CommandsBarHeight))
		{
			///TODO: SetHCell and SetVCell of the object cellPost appropriately
			//       using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)
			
			//start of adjustments
			// 
			//subtracting the ToolBarHeight to get the position wrt the grid start
			int vCell = (y - UI.ToolBarHeight) / UI.CellHeight;

			//calculating the Horizantal cell
			int hCell = x / UI.CellWidth;

			//setting the cell pos using the setter functions
			cellPos.SetVCell(vCell);
			cellPos.SetHCell(hCell);
		}
		else
		{
			//Click outside of the grid results into an error
			cellPos.SetVCell(-1);
			cellPos.SetHCell(-1);

		}
		//end of adjusments
	}

	return cellPos;
}

//////////////////////////////////////////////////////////////////////////////////////////

int Input::GetSelectedCommandIndex() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	if ((y >= UI.height - UI.StatusBarHeight - (UI.CommandsBarHeight / 2) - UI.AvailableCommandsYOffset) && (y < UI.height - UI.StatusBarHeight - (UI.CommandsBarHeight / 2) + UI.AvailableCommandsYOffset))
	{
		if (x < (UI.width/2) + UI.AvailableCommandsTextWidth || x > (UI.width / 2) + UI.AvailableCommandsTextWidth + (UI.CommandItemWidth / 2) * MaxAvailableCommands)
			return -1;

		return (x - ((UI.width / 2) + UI.AvailableCommandsTextWidth + (2*UI.AvailableCommandsXOffset))) / (UI.CommandItemWidth / 2);
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////// 
