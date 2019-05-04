#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginIDs.h"
#include "ImageContainer.h"
#include "BlobLayer.h"


class PluginState
{
	std::unique_ptr<ImageContainer> latticeImage;
	std::unique_ptr<BlobLayer> blobLayer;

	AudioDeviceManager deviceManager;
    ApplicationCommandManager appCmdMgr;
	MidiKeyboardState keyboardState;

public:
	PluginState();
	~PluginState();
    
    bool loadLayout(ValueTree nodeIn);
    bool saveLayout();
    
    void resetBlobLayer();

	ImageContainer* getLatticeImage();
	BlobLayer* getBlobLayer();

	MidiKeyboardState* getKeyboardState();
	AudioDeviceManager* getAudioDeviceManager();
    ApplicationCommandManager* getAppCmdMgr();
    
    ValueTree stateNode;
};
