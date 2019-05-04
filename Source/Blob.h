/*
  ==============================================================================

    Blob.h
    Created: 1 May 2019 6:52:39pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginIDs.h"

class Blob : public Component
{
	Point<float> center; // the center point of the blob layer
	float radius;
	int midiNote = -1;
	float alphaDefault = 0.3;
    
    int index = -1;

	bool on = false;
	bool selected = false;
	bool placed = false;
	
public:

	Blob();
	Blob(Point<float> centerIn, float radiusIn, Colour colorIn, int indexIn);
	Blob(Blob& blobToCopy);
    Blob(ValueTree nodeIn);
    
    void initiateNode();
	
	Point<float> getCenterPosition();
	float getAlphaDefault();
	int getMidiNote();
    int getIndex();
    
	bool isOn();
	bool isSelected();
	bool isPlaced();

    void setColor(Colour colorIn);
	void setAlphaDefault(float alphaIn);
	void setCenter(float xIn, float yIn);
	void setRadius(float radiusIn);
	void setMidiNote(int noteIn);
	void setOn(bool isOnIn = true);
	void setSelected(bool selectionIn = true);
	void setPlaced(bool placedIn = true);
    
    void setIndex(int indexIn);
    
    ValueTree blobNode;
};
