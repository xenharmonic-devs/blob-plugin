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


	loadImageBtn.reset(new TextButton("Load Image Button"));
	addAndMakeVisible(loadImageBtn.get());
	loadImageBtn->setButtonText("Load Image");
	loadImageBtn->setSize(133, 65);
	loadImageBtn->addListener(this);
	

	blobLayer = pluginState->getBlobLayer();
	addChildComponent(blobLayer);


	processor.getKeyboardState()->addListener(this);
	addMouseListener(this, true);

	setRepaintsOnMouseActivity(true);

    setSize (800, 500);
}

BlobpluginAudioProcessorEditor::~BlobpluginAudioProcessorEditor()
{
	processor.getKeyboardState()->removeListener(this);
}

void BlobpluginAudioProcessorEditor::setPlayMode()
{
	loadImageBtn->setVisible(false);
	blobLayer->setVisible(true);
}

void BlobpluginAudioProcessorEditor::setLoadMode()
{
	loadImageBtn->setVisible(true);
	blobLayer->setVisible(false);
}


//==============================================================================
void BlobpluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	if (latticeImage->getImage().isValid())
	{
		g.drawImage(latticeImage->getImage(), getBounds().toFloat());
	}
}

void BlobpluginAudioProcessorEditor::resized()
{
	latticeImage->setBounds(getBounds());
	blobLayer->setBounds(getBounds());
	loadImageBtn->setCentrePosition(getWidth() / 2, getHeight() / 2);
}

//==============================================================================

void BlobpluginAudioProcessorEditor::mouseDown(const MouseEvent& e)
{
	if (latticeImage->getImage().isValid())
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

	if (loadImageBtn->isMouseOver())
	{
		loadImageBtn->triggerClick();
	}
}

//==============================================================================

void BlobpluginAudioProcessorEditor::buttonClicked(Button* buttonClicked)
{
	if (buttonClicked == loadImageBtn.get())
	{
		if (latticeImage->browseAndLoad())
		{
			setPlayMode();
		}
	}
}


void BlobpluginAudioProcessorEditor::handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
	Blob* blobToMap = blobLayer->getSelection();
	
	DBG("On" + String(midiNoteNumber));
	if (blobToMap)
	{
		DBG("mapping blob");
		blobToMap->setMidiNote(midiNoteNumber);
	}

	blobLayer->triggerNoteOn(midiChannel, midiNoteNumber, velocity);
}

void BlobpluginAudioProcessorEditor::handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
	DBG("Off" + String(midiNoteNumber));
	blobLayer->triggerNoteOff(midiChannel, midiNoteNumber, velocity);
}