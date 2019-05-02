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
	color = Colours::transparentBlack;
	setColour(0, color);

	setBounds(0, 0, 1, 1);
}

Blob::Blob(Point<float> centerIn, float radiusIn, Colour colorIn)
{
	center = centerIn;
	radius = radiusIn;
	color = colorIn;
	setColour(0, color);

	setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
}

Blob::Blob(Blob& blobToCopy)
{
	center = blobToCopy.getCenterPosition();
	radius = blobToCopy.getWidth() / 2.0;
	color = blobToCopy.findColour(0);

	setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
}


Point<float> Blob::getCenterPosition()
{
	return Point<float>(getX() + radius, getY() + radius);
}

bool Blob::getMidiNote()
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

void Blob::setMidiNote(int noteIn)
{
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

void Blob::paint(Graphics& g)
{
	if (!on)
		g.setColour(color.withAlpha(0.3f));
	else
		g.setColour(color.withAlpha(0.6f));

	g.fillEllipse(getBounds().toFloat());

	if (selected)
	{
		g.setColour(Colours::black);
		g.drawRect(getBounds());
	}
}

void Blob::resized()
{

}