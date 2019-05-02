/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BlobpluginAudioProcessor::BlobpluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
	pluginState(new PluginState())
#endif
{
}

BlobpluginAudioProcessor::~BlobpluginAudioProcessor()
{
}

//==============================================================================


MidiKeyboardState* BlobpluginAudioProcessor::getKeyboardState()
{
	return keyboardState.get();
}

PluginState* BlobpluginAudioProcessor::getPluginState()
{
	return pluginState.get();
}

//==============================================================================
const String BlobpluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BlobpluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BlobpluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BlobpluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BlobpluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BlobpluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BlobpluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BlobpluginAudioProcessor::setCurrentProgram (int index)
{
}

const String BlobpluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void BlobpluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BlobpluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BlobpluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BlobpluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BlobpluginAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

	auto midiEvent = MidiBuffer::Iterator(midiMessages);
	MidiMessage msg;
	int smpl;

	while (midiEvent.getNextEvent(msg, smpl))
	{
		keyboardState->processNextMidiEvent(msg);
	}
}

//==============================================================================
bool BlobpluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BlobpluginAudioProcessor::createEditor()
{
    return new BlobpluginAudioProcessorEditor (*this);
}

//==============================================================================
void BlobpluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BlobpluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BlobpluginAudioProcessor();
}
