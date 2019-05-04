/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginIDs.h"
#include "MenuBar.h"
#include "ColorPickerWindow.h"
#include "ImageContainer.h"
#include "BlobLayer.h"

//==============================================================================
/**
*/
class BlobpluginAudioProcessorEditor  : public AudioProcessorEditor,
										public ApplicationCommandTarget,
										private MidiKeyboardStateListener,
										private Button::Listener,
                                        private ChangeListener
{
public:
    BlobpluginAudioProcessorEditor (BlobpluginAudioProcessor&);
    ~BlobpluginAudioProcessorEditor();

	//==============================================================================
    
    bool loadLayout();
    bool saveLayout();

	void setPlayMode();
	void setLoadMode();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	//==============================================================================
		
	void mouseDown(const MouseEvent& e) override;
	void mouseDrag(const MouseEvent& e) override;
	void mouseUp(const MouseEvent& e) override;

	//==============================================================================

	void modifierKeysChanged(const ModifierKeys& modifiers) override;

	//==============================================================================

	void handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState* source,int midiChannel, int midiNoteNumber, float velocity) override;

	//==============================================================================

	void buttonClicked(Button* buttonClicked) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

	//==============================================================================

	ApplicationCommandTarget* getNextCommandTarget() override;
	void getAllCommands(Array< CommandID > &commands) override;
	void getCommandInfo(CommandID commandID, ApplicationCommandInfo &result) override;
	bool perform(const InvocationInfo &info) override;


private:
	std::unique_ptr<MenuBarComponent> menuBar;
	std::unique_ptr<TextButton> loadImageBtn;
	std::unique_ptr<ColorPickerWindow> colorPickerWindow;

	ApplicationCommandManager* appCmdMgr;
	BlobMenuBar blobMenuModel;
    
	BlobpluginAudioProcessor& processor;
	PluginState* pluginState;
	ImageContainer* latticeImage;
	BlobLayer* blobLayer;

	// Locks
	bool shiftHeld = false;
	bool ctrlHeld = false;
	bool altHeld = false;
	//bool rightMouseDown = false;

	int menuBarHeight = 24;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlobpluginAudioProcessorEditor)
};
