/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ImageContainer.h"
#include "BlobLayer.h"

//==============================================================================
/**
*/
class BlobpluginAudioProcessorEditor  : public AudioProcessorEditor,
										private MidiKeyboardStateListener,
										private Button::Listener
{
public:
    BlobpluginAudioProcessorEditor (BlobpluginAudioProcessor&);
    ~BlobpluginAudioProcessorEditor();

	//==============================================================================

	void setPlayMode();
	void setLoadMode();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	//==============================================================================
		
	void mouseDown(const MouseEvent& e) override;

	//==============================================================================

	void handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity);
	void handleNoteOff(MidiKeyboardState* source,int midiChannel, int midiNoteNumber, float velocity);

	//==============================================================================

	void buttonClicked(Button* buttonClicked) override;

private:

	std::unique_ptr<TextButton> loadImageBtn;
    
	BlobpluginAudioProcessor& processor;
	PluginState* pluginState;
	ImageContainer* latticeImage;
	BlobLayer* blobLayer;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlobpluginAudioProcessorEditor)
};
