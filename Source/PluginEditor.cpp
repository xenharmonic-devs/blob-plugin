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
    : AudioProcessorEditor (&p), processor (p), blobMenuModel(p.getPluginState()->getAppCmdMgr())
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
    addChildComponent(colorPickerWindow.get());
	colorPickerWindow->addToDesktop();
    colorPickerWindow.get()->registerListener(this);

	processor.getKeyboardState()->addListener(this);
	addMouseListener(this, true);
	setRepaintsOnMouseActivity(true);
    
    appCmdMgr = pluginState->getAppCmdMgr();
    appCmdMgr->setFirstCommandTarget(this);
    appCmdMgr->registerAllCommandsForTarget(this);
    
    if (pluginState->stateNode.hasProperty(IDs::imagePath))
    {
        setPlayMode();
    }

    setSize (800, 500 + menuBarHeight);
}

BlobpluginAudioProcessorEditor::~BlobpluginAudioProcessorEditor()
{
	processor.getKeyboardState()->removeListener(this);
	menuBar->setModel(nullptr);
}

//==============================================================================

bool BlobpluginAudioProcessorEditor::loadLayout()
{
    FileChooser chooser("Load your layout...", File::getSpecialLocation(File::userDocumentsDirectory), "*.blob");
    chooser.browseForFileToOpen();
    
    File fileToLoad = File(chooser.getResult());
    
    if (fileToLoad.exists())
    {
        std::unique_ptr<XmlElement> xml = parseXML(chooser.getResult());
    
        if (pluginState->loadLayout(ValueTree::fromXml(*(xml.get()))))
        {
            removeChildComponent(blobLayer);
            blobLayer = pluginState->getBlobLayer();
            addChildComponent(blobLayer);
            setPlayMode();
            return true;
        }
    }
    return false;
}

bool BlobpluginAudioProcessorEditor::saveLayout()
{
    return pluginState->saveLayout();
}

void BlobpluginAudioProcessorEditor::setPlayMode()
{
	loadImageBtn->setVisible(false);
	blobLayer->setVisible(true);
    blobLayer->changeSelection(nullptr);
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
				blobLayer->addBlob(e.mouseDownPosition, 15, colorPickerWindow->getColor());
		}

		else if (!e.mods.isRightButtonDown())
        {
			blobLayer->changeSelection(blobClicked);
            
            if (blobClicked)
                colorPickerWindow->setColor(blobClicked->findColour(0).withAlpha(blobClicked->getAlphaDefault()));
        }
		else
		{
			blobLayer->removeBlob(blobClicked);
			blobLayer->changeSelection(blobClicked);
		}

		blobLayer->repaint();
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
            pluginState->stateNode.setProperty(IDs::imagePath, latticeImage->getImagePath(), nullptr);
            removeChildComponent(blobLayer);
            pluginState->resetBlobLayer();
            blobLayer = pluginState->getBlobLayer();
            addChildComponent(blobLayer);
			setPlayMode();
		}
	}
}

void BlobpluginAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source)
{
    Component* c = dynamic_cast<Component*>(source);
    
    if (c->getName() == "The Color Picker")
    {
        Blob* blobSelected = blobLayer->getSelection();
        
        if (blobSelected)
        {
            blobSelected->setColor(colorPickerWindow->getColor().withAlpha(0.0f));
            blobSelected->setAlphaDefault(colorPickerWindow->getColor().getFloatAlpha());
            blobSelected->repaint();
        }
    }
}

//==============================================================================


void BlobpluginAudioProcessorEditor::handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
	Blob* blobToMap = blobLayer->getSelection();
	
	if (blobToMap)
	{
		blobToMap->setMidiNote(midiNoteNumber);
	}

	blobLayer->triggerNoteOn(midiChannel, midiNoteNumber, velocity);
}

void BlobpluginAudioProcessorEditor::handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
	blobLayer->triggerNoteOff(midiChannel, midiNoteNumber, velocity);
}

//==============================================================================


ApplicationCommandTarget* BlobpluginAudioProcessorEditor::getNextCommandTarget()
{
	return findFirstTargetParentComponent();
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
            saveLayout();
		break;
	case CommandIDs::loadLayout:
            loadLayout();
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

	return true;
}
