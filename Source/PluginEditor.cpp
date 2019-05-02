/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BlobpluginAudioProcessorEditor::BlobpluginAudioProcessorEditor (BlobpluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	processor.getKeyboardState()->addListener(this);
	pluginState = processor.getPluginState();
	latticeImage = pluginState->getLatticeImage();
	blobLayer = pluginState->getBlobLayer();

    setSize (latticeImage->getImage().getWidth(), latticeImage->getImage().getHeight());
}

BlobpluginAudioProcessorEditor::~BlobpluginAudioProcessorEditor()
{
	processor.getKeyboardState()->removeListener(this);
}

//==============================================================================
void BlobpluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	g.drawImage(latticeImage->getImage(), getBounds().toFloat());
}

void BlobpluginAudioProcessorEditor::resized()
{
	latticeImage->setBounds(getBounds());
	blobLayer->setBounds(getBounds());
}

//==============================================================================

void BlobpluginAudioProcessorEditor::handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{

}

void BlobpluginAudioProcessorEditor::handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{

}