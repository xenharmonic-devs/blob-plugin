/*
  ==============================================================================

    Blob.cpp
    Created: 1 May 2019 6:52:39pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "Blob.h"

Blob::Blob()
{
	center = Point<float>();
	radius = 0;
	setColour(0, Colours::yellow);

	setBounds(0, 0, 1, 1);
}

Blob::Blob(Point<float> centerIn, float radiusIn)
{
	center = centerIn;
	radius = radiusIn;
	setColour(0, Colours::yellow);

	setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
}

Blob::Blob(Blob& blobToCopy)
{
	center = blobToCopy.getCenterPosition();
	radius = blobToCopy.getWidth() / 2.0;
	setColour(0, Colours::yellow);
	
	setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
}

void Blob::setCenter(float xIn, float yIn)
{
	center = Point<float>(xIn, yIn);
}

Point<float> Blob::getCenterPosition()
{
	return center;
}

float Blob::getAlphaDefault()
{
	return alphaDefault;
}

int Blob::getMidiNote()
{
	return midiNote;
}

bool Blob::isOn()
{
	return on;
}

bool Blob::isSelected()
{
	return selected;
}

bool Blob::isPlaced()
{
	return placed;
}

void Blob::setRadius(float radiusIn)
{
	radius = radiusIn;
	setSize(radius * 2, radius * 2);
}

void Blob::setAlphaDefault(float alphaIn)
{
	alphaDefault = alphaIn;
}

void Blob::setMidiNote(int noteIn)
{
	DBG("I'm a blob getting mapped to " + String(noteIn));
	midiNote = noteIn;
}

void Blob::setOn(bool isOnIn)
{
	on = isOnIn;
}

void Blob::setSelected(bool selectionIn)
{
	selected = selectionIn;
}

void Blob::setPlaced(bool placedIn)
{
	placed = placedIn;
}