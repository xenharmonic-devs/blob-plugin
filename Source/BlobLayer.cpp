/*
  ==============================================================================

    BlobLayer.cpp
    Created: 1 May 2019 6:53:19pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "BlobLayer.h"

BlobLayer::BlobLayer()
{
	setOpaque(false);
	setSize(50, 50);
}

BlobLayer::~BlobLayer()
{

}

Blob* BlobLayer::addBlob(Blob* blobIn)
{
	Blob* blobAdded = blobs.add(blobIn);
	addAndMakeVisible(blobAdded);

	blobPositions.add(Point<float>(blobAdded->getCenterPosition().x / getWidth(),
							       blobAdded->getCenterPosition().y / getHeight()));

	return blobAdded;
}

Blob* BlobLayer::addBlob(Point<float> centerIn, float radiusIn, Colour colorIn)
{
	return addBlob(new Blob(centerIn, radiusIn, colorIn));
}

void BlobLayer::paint(Graphics& g)
{
	g.setColour(Colours::aliceblue);
	g.fillAll();
}

void BlobLayer::resized()
{
	int i = 0;
	for (auto blob : blobs)
	{
		blob->setCentreRelative(blobPositions[i].x, blobPositions[i].y);
		i++;
	}
}