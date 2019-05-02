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
										private MidiKeyboardStateListener
{
public:
    BlobpluginAudioProcessorEditor (BlobpluginAudioProcessor&);
    ~BlobpluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	//==============================================================================

	void handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity);
	void handleNoteOff(MidiKeyboardState* source,int midiChannel, int midiNoteNumber, float velocity);

private:
    
	BlobpluginAudioProcessor& processor;
	PluginState* pluginState;
	ImageContainer* latticeImage;
	BlobLayer* blobLayer;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlobpluginAudioProcessorEditor)
};
