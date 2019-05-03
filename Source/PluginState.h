

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ImageContainer.h"
#include "BlobLayer.h"


class PluginState
{

	std::unique_ptr<ImageContainer> latticeImage;
	std::unique_ptr<BlobLayer> blobLayer;

	AudioDeviceManager deviceManager;
	MidiKeyboardState keyboardState;

public:
	PluginState();
	~PluginState();

	ImageContainer* getLatticeImage();
	BlobLayer* getBlobLayer();

	MidiKeyboardState* getKeyboardState();
	AudioDeviceManager* getAudioDeviceManager();
};

enum CommandIDs
{
	saveLayout = 1,
	loadLayout,
	loadImage,
	showColorPicker
};

namespace IDs
{
	static Identifier stateNode("StateNode");
	static Identifier imagePath("ImagePath");

	static Identifier blobLayerNode("BlobLayerNode");

	static Identifier blobNode("BlobNode");
	static Identifier blobCenter("BlobCenter");
	static Identifier blobRadius("BlobRadius");
	static Identifier blobColor("BlobColor");
	static Identifier blobAlpha("BlobAlpha");
}