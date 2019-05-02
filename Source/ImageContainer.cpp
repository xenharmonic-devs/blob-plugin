/*
  ==============================================================================

    ImageContainer.cpp
    Created: 1 May 2019 6:52:29pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "ImageContainer.h"


ImageContainer::ImageContainer(String name)
{
	setName(name);
}

ImageContainer::ImageContainer(String name, File fileIn)
{
	setName(name);

	if (loadFile(fileIn))
	{
		ImageComponent::setImage(theImage);
	}
}

ImageContainer::~ImageContainer()
{

}

bool ImageContainer::browseAndLoad()
{
	fileChooser.reset(new FileChooser("Choose an image...", File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory),
		String("*.jpg; *.jpeg; *.png; *.gif")));

	fileChooser->browseForFileToOpen();

	if (loadFile(fileChooser->getResult()))
	{
		ImageComponent::setImage(theImage);
		return true;
	}
	return false;
}

bool ImageContainer::loadFile(File fileIn)
{
	imageFile = fileIn;
	imagePath = imageFile.getFullPathName();

	// attempt to load file
	inputStream.reset(new FileInputStream(imageFile));

	if (jpegFormat.usesFileExtension(imageFile))
	{
		theImage = jpegFormat.decodeImage(*inputStream.get());
		return true;
	}
	else if (pngFormat.usesFileExtension(imageFile))
	{
		theImage = pngFormat.decodeImage(*inputStream.get());
		return true;
	}
	else if (gifFormat.usesFileExtension(imageFile))
	{
		theImage = gifFormat.decodeImage(*inputStream.get());
		return true;
	}
	else
	{
		// do something
	}
	return false;
}