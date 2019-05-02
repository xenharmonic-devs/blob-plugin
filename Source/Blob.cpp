/*
  ==============================================================================

    Blob.cpp
    Created: 1 May 2019 6:52:39pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "Blob.h"

Blob::Blob(Point<float> centerIn, float radiusIn, Colour colorIn)
{
	center = centerIn;
	radius = radiusIn;

	setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
	setOpaque(false);
}

Point<float> Blob::getCenterPosition()
{
	return Point<float>(getX() + radius, getY() + radius);
}

void Blob::setMidiNote(int noteIn)
{
	midiNote = noteIn;
}

void Blob::paint(Graphics& g)
{
	g.setColour(color);
	g.fillEllipse(getBounds().toFloat());
}

void Blob::resized()
{

}