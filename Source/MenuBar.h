/*
  ==============================================================================

    MenuBar.h
    Created: 2 May 2019 10:32:27pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginState.h"

class BlobMenuBar : public MenuBarModel
{
	ApplicationCommandManager* appCmdMgr;

public:

	BlobMenuBar(ApplicationCommandManager* cmdManagerIn);
	~BlobMenuBar();

	StringArray getMenuBarNames() override;

	PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;

	void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
};