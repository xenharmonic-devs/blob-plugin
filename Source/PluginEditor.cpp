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
    : AudioProcessorEditor (&p), processor (p), blobMenuModel(&appCmdMgr)
{
	pluginState = processor.getPluginState();
	latticeImage = pluginState->getLatticeImage();

	menuBar.reset(new MenuBarComponent(&blobMenuModel));
	addAndMakeVisible(menuBar.get());

	loadImageBtn.reset(new TextButton("Load Image Button"));
	addAndMakeVisible(loadImageBtn.get());
	loadImageBtn->setButtonText("Load Image");
	loadImageBtn->setSize(133, 65);
	loadImageBtn->addListener(this);
	
	blobLayer = pluginState->getBlobLayer();
	addChildComponent(blobLayer);

	colorPickerWindow.reset(new ColorPickerWindow);
	colorPickerWindow->addToDesktop();

	processor.getKeyboardState()->addListener(this);
	addMouseListener(this, true);
	setRepaintsOnMouseActivity(true);

	appCmdMgr.registerAllCommandsForTarget(this);

    setSize (800, 500 + menuBarHeight);
}

BlobpluginAudioProcessorEditor::~BlobpluginAudioProcessorEditor()
{
	processor.getKeyboardState()->removeListener(this);
	menuBar->setModel(nullptr);
}

void BlobpluginAudioProcessorEditor::setPlayMode()
{
	loadImageBtn->setVisible(false);
	blobLayer->setVisible(true);
	setSize(latticeImage->getImage().getWidth(), latticeImage->getImage().getHeight() + menuBarHeight);
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
		g.drawImage(latticeImage->getImage(), latticeImage->getBounds().toFloat());
	}
}

void BlobpluginAudioProcessorEditor::resized()
{
	menuBar->setBounds(0, 0, getWidth(), menuBarHeight);
	latticeImage->setBounds(getBounds().withTop(menuBarHeight));
	blobLayer->setBounds(getBounds().withTop(menuBarHeight));
	loadImageBtn->setCentrePosition(getWidth() / 2, getHeight() / 2);
}

//==============================================================================

void BlobpluginAudioProcessorEditor::mouseDown(const MouseEvent& e)
{
	if (latticeImage->getImage().isValid())
	{
		Blob* blobClicked = dynamic_cast<Blob*>(e.eventComponent);

		if (!e.mods.isRightButtonDown() && ctrlHeld)
		{
			if (!blobClicked)
				blobLayer->addBlob(e.mouseDownPosition, 10);
		}

		else if (!e.mods.isRightButtonDown())
			blobLayer->changeSelection(blobClicked);

		else
		{
			blobLayer->removeBlob(blobClicked);
			blobLayer->changeSelection(blobClicked);
		}

		blobLayer->repaint();
		DBG(blobLayer->getNumBlobs());
	}
}

void BlobpluginAudioProcessorEditor::mouseDrag(const MouseEvent& e)
{
	if (latticeImage->getImage().isValid())
	{
		Blob* blobClicked = dynamic_cast<Blob*>(e.eventComponent);

		if (blobClicked)
		{
			const MouseEvent e1 = e.getEventRelativeTo(this);
			const MouseEvent m = e1.withNewPosition(Point<float>(e1.x, e1.y - menuBarHeight));

			if (!e.mods.isRightButtonDown() && shiftHeld)
			{	
				int distFromBlobCenter = sqrt(
					pow(m.getPosition().x - blobClicked->getCenterPosition().x * getWidth(), 2) +
					pow(m.getPosition().y - blobClicked->getCenterPosition().y * getHeight(), 2));

				blobLayer->resizeBlob(blobClicked, distFromBlobCenter);
			}

			else if (!e.mods.isRightButtonDown())
			{
				blobLayer->moveBlob(blobClicked, m);
			}

			else if (e.mods.isRightButtonDown())
				blobLayer->removeBlob(blobClicked);
		}
	}
}

void BlobpluginAudioProcessorEditor::mouseUp(const MouseEvent& e)
{

}

//==============================================================================

void BlobpluginAudioProcessorEditor::modifierKeysChanged(const ModifierKeys& modifiers)
{
	if (!shiftHeld && modifiers.isShiftDown())
	{
		shiftHeld = true;
	}

	if (shiftHeld && !modifiers.isShiftDown())
	{
		shiftHeld = false;
	}

	if (!ctrlHeld && modifiers.isCtrlDown())
	{
		ctrlHeld = true;
	}

	if (ctrlHeld && !modifiers.isCtrlDown())
	{
		ctrlHeld = false;
	}

	if (!altHeld && modifiers.isAltDown())
	{
		altHeld = true;
	}

	if (altHeld && !modifiers.isAltDown())
	{
		altHeld = false;
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

//==============================================================================


ApplicationCommandTarget* BlobpluginAudioProcessorEditor::getNextCommandTarget()
{
	return this;
}

void BlobpluginAudioProcessorEditor::getAllCommands(Array< CommandID > &c)
{
	Array<CommandID> commands{
		CommandIDs::saveLayout,
		CommandIDs::loadLayout,
		CommandIDs::showColorPicker,
		CommandIDs::loadImage,
	};

	c.addArray(commands);
}

void BlobpluginAudioProcessorEditor::getCommandInfo(CommandID commandID, ApplicationCommandInfo &result)
{
	switch (commandID)
	{
	case CommandIDs::saveLayout:
		result.setInfo("Save Layout", "Save your layout to a file.", "Main", 0);
		break;
	case CommandIDs::loadLayout:
		result.setInfo("Load Layout", "Load a layout from a file.", "Main", 0);
		break;
	case CommandIDs::showColorPicker:
		result.setInfo("Show Color Picker", "Show color picker to change blob colors.", "Main", 0);
		break;
	case CommandIDs::loadImage:
		result.setInfo("Load Image", "Load new \"Lattic\" image.", "Main", 0);
		break;
	default:
		break;
	}
}

bool BlobpluginAudioProcessorEditor::perform(const InvocationInfo &info)
{
	switch (info.commandID)
	{
	case CommandIDs::saveLayout:
		
		break;
	case CommandIDs::loadLayout:
		
		break;
	case CommandIDs::showColorPicker:
		colorPickerWindow->setVisible(true);
		break;
	case CommandIDs::loadImage:
		loadImageBtn->triggerClick();
		break;
	default:
		break;
	}

	return false;
}