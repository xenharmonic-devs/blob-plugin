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
	changeSelection(blobAdded);

	blobPositions.add(Point<float>(blobAdded->getCenterPosition().x / getWidth(),
							       blobAdded->getCenterPosition().y / getHeight()));

	return blobAdded;
}

Blob* BlobLayer::addBlob(Point<float> centerIn, float radiusIn, Colour colorIn)
{
	return addBlob(new Blob(centerIn, radiusIn, colorIn));
}

void BlobLayer::removeBlob(Blob* blobOut)
{
	blobs.removeObject(blobOut, true);
}

bool BlobLayer::changeSelection(Blob* blobSelectedIn)
{
	if (blobs.contains(blobSelectedIn))
	{
		blobSelected->setSelected(false);
		blobSelectedIn->setSelected();
		blobSelected = blobSelectedIn;
		return true;
	}

	blobSelected->setSelected(false);

	return false;
}

Blob* BlobLayer::getSelection()
{
	if (blobSelected->isSelected())
		return blobSelected;
	else
		return nullptr;
}

int BlobLayer::getNumBlobs()
{
	return blobs.size();
}

void BlobLayer::triggerNoteOn(int midiChannel, int midiNoteNumber, float velocity)
{
	for (auto blob : blobs)
	{
		if (blob->getMidiNote() == midiNoteNumber)
		{
			blob->setOn();
			blob->repaint();
		}
	}
}

void BlobLayer::triggerNoteOff(int midiChannel, int midiNoteNumber, float velocity)
{
	for (auto blob : blobs)
	{
		if (blob->getMidiNote() == midiNoteNumber)
		{
			blob->setOn(false);
			blob->repaint();
		}
	}
}

void BlobLayer::paint(Graphics& g)
{
	g.setColour(Colours::black);
	g.drawRect(getBounds());

	for (auto blob : blobs)
	{
		blob->paint(g);
	}
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