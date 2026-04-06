#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WyldKardAudioProcessor::WyldKardAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // 1. Allow the plugin to read common audio formats
    formatManager.registerBasicFormats();
}

WyldKardAudioProcessor::~WyldKardAudioProcessor()
{
}

//==============================================================================
// This is the function called by your React UI via the PluginEditor
void WyldKardAudioProcessor::previewSample (const juce::String& sampleName)
{
    // Update this path to your actual samples folder
    juce::File sampleFile = juce::File::"C:\Users\capci\Music"(juce::File::userHomeDirectory)
                            .getChildFile("Music/Samples")
                            .getChildFile(sampleName + ".wav");

    if (sampleFile.existsAsFile())
    {
        auto* reader = formatManager.createReaderFor (sampleFile);

        if (reader != nullptr)
        {
            auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
            
            // Stop current playback and load the new sample
            transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset (newSource.release());
            transportSource.start();
        }
    }
}

void WyldKardAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    transportSource.prepareToPlay (samplesPerBlock, sampleRate);
}

void WyldKardAudioProcessor::releaseResources()
{
    transportSource.releaseResources();
}

void WyldKardAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear the buffer to prevent noise
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Send the audio from our sample player to the output
    juce::AudioSourceChannelInfo bufferToFill (buffer);
    transportSource.getNextAudioBlock (bufferToFill);
}

//==============================================================================
// Standard JUCE Required Methods
//==============================================================================

const juce::String WyldKardAudioProcessor::getName() const { return JucePlugin_Name; }
bool WyldKardAudioProcessor::acceptsMidi() const { return true; }
bool WyldKardAudioProcessor::producesMidi() const { return false; }
bool WyldKardAudioProcessor::isMidiEffect() const { return false; }
double WyldKardAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int WyldKardAudioProcessor::getNumPrograms() { return 1; }
int WyldKardAudioProcessor::getCurrentProgram() { return 0; }
void WyldKardAudioProcessor::setCurrentProgram (int index) {}
const juce::String WyldKardAudioProcessor::getProgramName (int index) { return {}; }
void WyldKardAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

bool WyldKardAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* WyldKardAudioProcessor::createEditor() 
{ 
    return new WyldKardAudioProcessorEditor (*this); 
}

void WyldKardAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}
void WyldKardAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

// This creates the processor instance
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WyldKardAudioProcessor();
}
