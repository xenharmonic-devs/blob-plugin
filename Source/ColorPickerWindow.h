/*
  ==============================================================================

    ColorPickerWindow.h
    Created: 2 May 2019 10:10:01pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ColorPickerWindow : public DocumentWindow
{
	std::unique_ptr<ColourSelector> colorPicker;

public:

	ColorPickerWindow()
		: DocumentWindow("Choose Color for Selected Blob", Colours::slateblue, TitleBarButtons::closeButton)
	{
		colorPicker.reset(new ColourSelector());
		setContentComponent(colorPicker.get());
		
		setSize(375, 375);
	}

	~ColorPickerWindow()
	{
		setVisible(false);
	}
};