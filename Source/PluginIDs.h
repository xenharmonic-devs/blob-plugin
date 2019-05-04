/*
  =============================================================================

    PluginIDs.
    Created: 3 May 2019 7:11:44p
    Author:  Vincenz

  =============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

enum CommandIDs
{
	saveLayout = 1,
	loadLayout,
	loadImage,
	showColorPicker
};

namespace IDs
{
	static Identifier stateNode("StateNode");
	static Identifier imagePath("ImagePath");

	static Identifier blobLayerNode("BlobLayerNode");

	static Identifier blobNode("BlobNode");
	static Identifier blobCenterX("BlobCenterX");
    static Identifier blobCenterY("BlobCenterY");
	static Identifier blobRadius("BlobRadius");
	static Identifier blobColor("BlobColor");
	static Identifier blobAlpha("BlobAlpha");
    static Identifier blobMidiNote("BlobMidiNote");
    static Identifier blobIndex("BlobIndexs");

}
