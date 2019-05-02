/*
  ==============================================================================

    BlobLayer.h
    Created: 1 May 2019 6:53:19pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Blob.h"

class BlobLayer : public Component
{

	OwnedArray<Blob> blobs;
	Array<Point<float>> blobPositions;
	Blob dummy = Blob();

	Blob* blobSelected = &dummy;

public:

	BlobLayer();
	~BlobLayer();

	Blob* addBlob(Blob* blobIn);
	Blob* addBlob(Point<float> centerIn, float radiusIn, Colour colorIn = Colours::yellow);

	void removeBlob(Blob* blobOut);

	bool changeSelection(Blob* blobSelectedIn);

	Blob* getSelection();
	int getNumBlobs();

	void triggerNoteOn(int midiChannel, int midiNoteNumber, float velocity);
	void triggerNoteOff(int midiChannel, int midiNoteNumber, float velocity);

	void paint(Graphics& g) override;
	void resized() override;
};