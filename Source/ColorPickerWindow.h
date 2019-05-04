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
        setName("ColorPickerWindow");
        
		colorPicker.reset(new ColourSelector());
		setContentOwned(colorPicker.get(), false);
        colorPicker->setName("The Color Picker");
        colorPicker->setCurrentColour(Colours::lightblue.withSaturation(1.0f).withAlpha(0.5f));
        
        setAlwaysOnTop(true);
		
		setSize(375, 375);
	}

	~ColorPickerWindow()
	{
		
	}
    
    void setColor(Colour colorIn)
    {
        colorPicker->setCurrentColour(colorIn);
    }
    
    Colour getColor()
    {
        return colorPicker->getCurrentColour();
    }
    
    void closeButtonPressed() override
    {
        setVisible(false);
    }
    
    void registerListener(ChangeListener* listenerIn)
    {
        colorPicker->addChangeListener(listenerIn);
    }
};
