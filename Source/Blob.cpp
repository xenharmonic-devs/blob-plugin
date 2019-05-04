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
    initiateNode();
}

Blob::Blob(Point<float> centerIn, float radiusIn, Colour colorIn, int indexIn)
{
	center = centerIn;
	radius = radiusIn;
	setColour(0, colorIn);
    index = indexIn;

	setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
    initiateNode();
}

Blob::Blob(Blob& blobToCopy)
{
	center = blobToCopy.getCenterPosition();
	radius = blobToCopy.getWidth() / 2.0;
	setColour(0, blobToCopy.findColour(0));
    alphaDefault = blobToCopy.getAlphaDefault();
    midiNote = blobToCopy.getMidiNote();
    index = blobToCopy.getIndex();
	
	setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
    initiateNode();
}

Blob::Blob(ValueTree nodeIn)
{
    if (nodeIn.hasType(IDs::blobNode))
    {
        center = Point<float>(nodeIn[IDs::blobCenterX], nodeIn[IDs::blobCenterY]);
        radius = nodeIn[IDs::blobRadius];
        setColour(0, Colour::fromString(nodeIn[IDs::blobColor].toString()));
        alphaDefault = nodeIn[IDs::blobAlpha];
        midiNote = nodeIn[IDs::blobMidiNote];
        index = nodeIn[IDs::blobIndex];
        
        blobNode = ValueTree(IDs::blobNode);
        blobNode.copyPropertiesFrom(nodeIn, nullptr);
        setBounds(center.x - radius, center.y - radius, radius * 2, radius * 2);
    }
    else
        Blob();
}

void Blob::initiateNode()
{
    blobNode = ValueTree(IDs::blobNode);
    
    blobNode.setProperty(IDs::blobCenterX, center.x, nullptr);
    blobNode.setProperty(IDs::blobCenterY, center.y, nullptr);
    blobNode.setProperty(IDs::blobRadius, radius, nullptr);
    blobNode.setProperty(IDs::blobColor, findColour(0).toString(), nullptr);
    blobNode.setProperty(IDs::blobAlpha, alphaDefault, nullptr);
    blobNode.setProperty(IDs::blobMidiNote, midiNote, nullptr);
    blobNode.setProperty(IDs::blobIndex, index, nullptr);
}

void Blob::setCenter(float xIn, float yIn)
{
	center = Point<float>(xIn, yIn);
    blobNode.setProperty(IDs::blobCenterX, center.x, nullptr);
    blobNode.setProperty(IDs::blobCenterY, center.y, nullptr);
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

int Blob::getIndex()
{
    return index;
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
    blobNode.setProperty(IDs::blobRadius, radius, nullptr);
}

void Blob::setColor(Colour colorIn)
{
    setColour(0, colorIn);
    blobNode.setProperty(IDs::blobColor, findColour(0).toString(), nullptr);
}

void Blob::setAlphaDefault(float alphaIn)
{
	alphaDefault = alphaIn;
    blobNode.setProperty(IDs::blobAlpha, alphaDefault, nullptr);
}

void Blob::setMidiNote(int noteIn)
{
	midiNote = noteIn;
    blobNode.setProperty(IDs::blobMidiNote, midiNote, nullptr);
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

void Blob::setIndex(int indexIn)
{
    index = indexIn;
    blobNode.setProperty(IDs::blobIndex, index, nullptr);
}
