#include "PluginProcessor.h"
#include "PluginEditor.h"

WyldKardAudioProcessorEditor::WyldKardAudioProcessorEditor (WyldKardAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // 1. Initialise and display the web browser
    addAndMakeVisible (webBrowser);

    // // src/PluginEditor.cpp inside the sendToNative callback
if (var.getProperty("action", "").toString() == "OPEN_STEMS_FOLDER")
{
    juce::File stemDir = juce::File::getSpecialLocation(juce::File::userHomeDirectory)
                         .getChildFile("Music")
                         .getChildFile("WyldKard_Stems");
                         
    stemDir.revealToUser(); // This opens File Explorer/Finder exactly at that folder
}
if (var.getProperty("action", "").toString() == "REMAKE_UVR")
{
    auto path = var.getProperty("payload", "").getProperty("path", "").toString();
    auto model = var.getProperty("payload", "").getProperty("model", "").toString();
    
    // Trigger the AI processing in the engine
    audioProcessor.startUVRProcess(path, model);
}2. Map C++ functions to be visible in JavaScript
    webBrowser.addNativeFunction ("sendToNative", [this] (const juce::var& args) 
    {
        if (args.isArray() && args.size() > 0) 
        {
            auto jsonString = args[0].toString();
            auto var = juce::JSON::parse (jsonString);

            if (var.getProperty ("action", "").toString() == "PLAY_SAMPLE") 
            {
                auto sampleName = var.getProperty ("payload", "").getProperty ("name", "").toString();
                DBG ("JUCE: Received Play Request for: " << sampleName);
                
                // Call the Processor's version of this function
                audioProcessor.previewSample (sampleName);
            }
        }
    });

    // 3. Set the URL for the frontend
    webBrowser.goToURL ("http://localhost:5173"); 

    setSize (1000, 700);
}

WyldKardAudioProcessorEditor::~WyldKardAudioProcessorEditor() {}

void WyldKardAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void WyldKardAudioProcessorEditor::resized()
{
    webBrowser.setBounds (getLocalBounds());
}
