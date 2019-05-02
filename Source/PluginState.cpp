#include "PluginState.h"

PluginState::PluginState()
{
	//File defaultLattice = File(CharPointer_UTF8(BinaryData::Tonnetz_png));
	latticeImage.reset(new ImageContainer("Lattice"));
	blobLayer.reset(new BlobLayer());
	keyboardState.reset();
}


PluginState::~PluginState()
{
}

ImageContainer* PluginState::getLatticeImage()
{
	return latticeImage.get();
}

BlobLayer* PluginState::getBlobLayer()
{
	return blobLayer.get();
}

MidiKeyboardState* PluginState::getKeyboardState()
{
	return &keyboardState;
}