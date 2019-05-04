#include "PluginState.h"

PluginState::PluginState()
{
    stateNode = ValueTree(IDs::stateNode);
	latticeImage.reset(new ImageContainer("Lattice"));
	
    blobLayer.reset(new BlobLayer());
    stateNode.addChild(blobLayer->blobLayerNode, 0, nullptr);
    
	deviceManager.initialiseWithDefaultDevices(0, 0);
	keyboardState.reset();
}


PluginState::~PluginState()
{
}

bool PluginState::loadLayout(ValueTree nodeIn)
{
    if (nodeIn.isValid() && nodeIn.hasProperty(IDs::imagePath) && nodeIn.getChild(0).hasType(IDs::blobLayerNode))
    {
        latticeImage->loadFile(File(nodeIn[IDs::imagePath]));
        stateNode.setProperty(IDs::imagePath, nodeIn[IDs::imagePath], nullptr);

        blobLayer.reset(new BlobLayer(nodeIn.getChild(0)));
        stateNode.removeChild(0, nullptr);
        stateNode.addChild(blobLayer->blobLayerNode, 0, nullptr);
        return true;
    }
    
    return false;
}

bool PluginState::saveLayout()
{
    FileChooser chooser("Save your layout...", File::getSpecialLocation(File::userDocumentsDirectory), "*.blob");
    chooser.browseForFileToSave(true);
    File toSave(chooser.getResult());
    
    if (toSave.getParentDirectory().exists())
    {
        XmlElement* xml = stateNode.createXml();
        xml->writeToFile(chooser.getResult(), "");
        return true;
    }
    
    return false;
}

void PluginState::resetBlobLayer()
{
    blobLayer.reset(new BlobLayer());
    stateNode.removeChild(0, nullptr);
    stateNode.addChild(blobLayer->blobLayerNode, 0, nullptr);
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

AudioDeviceManager* PluginState::getAudioDeviceManager()
{
	return &deviceManager;
}

ApplicationCommandManager* PluginState::getAppCmdMgr()
{
    return & appCmdMgr;
}
