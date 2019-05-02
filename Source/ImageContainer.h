/*
  ==============================================================================

    ImageContainer.h
    Created: 1 May 2019 6:52:29pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ImageContainer : public ImageComponent
{
	// Data
	std::unique_ptr<FileChooser> fileChooser;
	File imageFile;
	String imagePath;
	Image theImage;

	// Functionality
	std::unique_ptr<FileInputStream> inputStream;
	JPEGImageFormat jpegFormat;
	PNGImageFormat pngFormat;
	GIFImageFormat gifFormat;

public:

	ImageContainer(String name);
	ImageContainer(String name, File fileIn);
	~ImageContainer();

	bool loadFile(File fileIn);

};