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
	int midiNote = -1;

	bool on = false;
	bool selected = false;
	bool placed = false;
	
public:

	Blob();
	Blob(Point<float> centerIn, float radiusIn, Colour colorIn = Colours::yellow);
	Blob(Blob& blobToCopy);
	
	Point<float> getCenterPosition();
	bool getMidiNote();
	bool isOn();
	bool isSelected();
	bool isPlaced();

	void setMidiNote(int noteIn);
	void setOn(bool isOnIn = true);
	void setSelected(bool selectionIn = true);
	void setPlaced(bool placedIn = true);

	void paint(Graphics& g) override;
	void resized() override;
};