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

	blobAdded->setName("Blob " + String(blobAdded->getCenterPosition().toString()));
	addAndMakeVisible(blobAdded);
	changeSelection(blobAdded);

	return blobAdded;
}

Blob* BlobLayer::addBlob(Point<float> centerIn, float radiusIn)
{
	return addBlob(new Blob(centerIn, radiusIn));
}

void BlobLayer::removeBlob(Blob* blobOut)
{
	blobs.removeObject(blobOut, true);
}

void BlobLayer::moveBlob(Blob* blobMoved, const MouseEvent& e)
{
	blobMoved->setCenter(e.x / (float)getWidth(), e.y / (float)getHeight());
	blobMoved->setCentreRelative(blobMoved->getCenterPosition().x, blobMoved->getCenterPosition().y);
	repaint();
}

void BlobLayer::resizeBlob(Blob* blobResized, float newSize)
{
	blobResized->setRadius(newSize);
	blobResized->setCentreRelative(blobResized->getCenterPosition().x, blobResized->getCenterPosition().y);
	repaint();
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
	Blob* blob;

	for (int i = 0; i < blobs.size(); i++)
	{
		blob = blobs.getUnchecked(i);

		if (blob->getMidiNote() == midiNoteNumber)
		{
			DBG("Found matching blob");
			blob->setOn();
			blob->repaint();
		}
	}
}

void BlobLayer::triggerNoteOff(int midiChannel, int midiNoteNumber, float velocity)
{
	Blob* blob;

	for (int i = 0; i < blobs.size(); i++)
	{
		blob = blobs.getUnchecked(i);

		if (blob->getMidiNote() == midiNoteNumber)
		{
			blob->setOn(false);
			blob->repaint();
		}
	}
}

void BlobLayer::paint(Graphics& g)
{	
	for (auto blob : blobs)
	{
		if (!blob->isOn())
			g.setColour(blob->findColour(0).withAlpha(blob->getAlphaDefault()));
		else
			g.setColour(blob->findColour(0).withAlpha(1.0f-blob->getAlphaDefault()));

		g.fillEllipse(blob->getBoundsInParent().toFloat());

		if (blob->isSelected())
		{
			g.setColour(Colours::black);
			g.drawRect(blob->getBoundsInParent());
		}
	}
	
}

void BlobLayer::resized()
{
	int i = 0;
	for (auto blob : blobs)
	{
		blob->setCentreRelative(blob->getCenterPosition().x, blob->getCenterPosition().y);
		i++;
	}
}