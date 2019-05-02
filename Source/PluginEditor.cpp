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
	pluginState = processor.getPluginState();
	latticeImage = pluginState->getLatticeImage();
	blobLayer = pluginState->getBlobLayer();

	addAndMakeVisible(blobLayer);

	processor.getKeyboardState()->addListener(this);
	addMouseListener(this, true);

	setRepaintsOnMouseActivity(true);

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

void BlobpluginAudioProcessorEditor::mouseDown(const MouseEvent& e)
{
	Blob* clickedBlob = dynamic_cast<Blob*>(e.eventComponent);

	if (!e.mods.isRightButtonDown())
	{
		if (!clickedBlob)
			blobLayer->addBlob(e.mouseDownPosition, 10, Colours::green);
		else
			blobLayer->changeSelection(clickedBlob);
	}
	else
	{
		blobLayer->removeBlob(clickedBlob);
		blobLayer->changeSelection(clickedBlob);
	}
	blobLayer->repaint();
	DBG(blobLayer->getNumBlobs());
}

//==============================================================================

void BlobpluginAudioProcessorEditor::timerCallback()
{
	
}


void BlobpluginAudioProcessorEditor::handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
	Blob* blobToMap = blobLayer->getSelection();

	if (blobToMap)
	{
		blobToMap->setMidiNote(midiNoteNumber);
	}

	blobLayer->triggerNoteOn(midiChannel, midiNoteNumber, velocity);
	DBG("On" + midiNoteNumber);
}

void BlobpluginAudioProcessorEditor::handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
	blobLayer->triggerNoteOff(midiChannel, midiNoteNumber, velocity);
	DBG("Off" + midiNoteNumber);
}