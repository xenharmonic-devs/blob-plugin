

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ImageContainer.h"
#include "BlobLayer.h"


class PluginState
{

	std::unique_ptr<ImageContainer> latticeImage;
	std::unique_ptr<BlobLayer> blobLayer;

public:
	PluginState();
	~PluginState();

	ImageContainer* getLatticeImage();
	BlobLayer* getBlobLayer();
};

