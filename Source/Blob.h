/*
  ==============================================================================

    Blob.h
    Created: 1 May 2019 6:52:39pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Blob : public Component
{

	Point<float> center;
	float radius;
	Colour color;

	int midiNote;
	
public:

	Blob(Point<float> centerIn, float radiusIn, Colour colorIn = Colours::yellow);
	
	Point<float> getCenterPosition();

	void setMidiNote(int noteIn);

	void paint(Graphics& g) override;
	void resized() override;
};