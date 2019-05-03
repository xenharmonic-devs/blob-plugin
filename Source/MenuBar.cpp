/*
  ==============================================================================

    MenuBar.cpp
    Created: 2 May 2019 10:32:27pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "MenuBar.h"

BlobMenuBar::BlobMenuBar(ApplicationCommandManager* cmdManagerIn)
	: appCmdMgr(cmdManagerIn) {};

BlobMenuBar::~BlobMenuBar() {};

StringArray BlobMenuBar::getMenuBarNames()
{
	return { "File", "Edit" };
}

PopupMenu BlobMenuBar::getMenuForIndex(int topLevelMenuIndex, const String& menuName)
{
	PopupMenu menu;

	if (topLevelMenuIndex == 0)
	{
		menu.addCommandItem(appCmdMgr, CommandIDs::saveLayout, "Save layout");
		menu.addCommandItem(appCmdMgr, CommandIDs::loadLayout, "Load layout");
		menu.addCommandItem(appCmdMgr, CommandIDs::loadImage, "Load  new \"Lattice\" image.");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addCommandItem(appCmdMgr, CommandIDs::showColorPicker, "Show Color Picker");
	}

	return menu;
}

void BlobMenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{

}