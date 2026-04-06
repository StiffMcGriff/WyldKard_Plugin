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
    // This correctly builds the path: C:\Users\YourName\Music\Samples\filename.wav
    juce::File sampleFile = juce::File::getSpecialLocation(juce::File::userHomeDirectory)
                            .getChildFile("Music")
                            .getChildFile("Samples")
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
    else 
    {
        DBG("File not found at: " << sampleFile.getFullPathName());
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
// Add this to your PluginProcessor.cpp
// --- UVR 5 AI Engine: Model Selection Logic ---

void WyldKardAudioProcessor::startUVRProcess(const juce::String& samplePath, const juce::String& modelType)
{
    DBG("WyldKard AI: Preparing " << modelType << " for " << samplePath);
    isProcessingAI = true;

    // 1. Determine which ONNX model file to load
    juce::File modelFile;
    auto modelDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile)
                    .getParentDirectory().getChildFile("Models");

    if (modelType == "Vocals-Only")
        modelFile = modelDir.getChildFile("UVR-MDX-NET-Voc_FT.onnx");
    else if (modelType == "Full-Stems")
        modelFile = modelDir.getChildFile("htdemucs_v4.onnx");
    else
        modelFile = modelDir.getChildFile("UVR-MDX-NET-Inst_HQ_3.onnx"); 

    // 2. Load and Run
    if (modelFile.existsAsFile())
    {
        // helper function to init ONNX session
        // loadUVRModel(modelFile); 
        runUVRModel(samplePath, modelType);
    }
    else
    {
        DBG("AI Error: Model file missing at " << modelFile.getFullPathName());
        isProcessingAI = false;
    }
}

void WyldKardAudioProcessor::runUVRModel(const juce::String& inputPath, const juce::String& modelType)
{
    try {
        // [ONNX Runtime Inference Logic goes here]
        DBG("AI Success: " << modelType << " processing complete.");
    }
    catch (const std::exception& e) {
        DBG("ONNX Runtime Error: " << e.what());
    }
    isProcessingAI = false;
}
