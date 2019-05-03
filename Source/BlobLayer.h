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
	Blob dummy = Blob();

	Blob* blobSelected = &dummy;

public:

	BlobLayer();
	~BlobLayer();

	Blob* addBlob(Blob* blobIn);
	Blob* addBlob(Point<float> centerIn, float radiusIn);

	void removeBlob(Blob* blobOut);
	void moveBlob(Blob* blobMoved, const MouseEvent& e);
	void resizeBlob(Blob* blobResized, float newSize);

	bool changeSelection(Blob* blobSelectedIn);

	Blob* getSelection();
	int getNumBlobs();

	void triggerNoteOn(int midiChannel, int midiNoteNumber, float velocity);
	void triggerNoteOff(int midiChannel, int midiNoteNumber, float velocity);

	void paint(Graphics& g) override;
	void resized() override;
};