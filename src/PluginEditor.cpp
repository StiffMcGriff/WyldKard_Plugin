#include "PluginProcessor.h"
#include "PluginEditor.h"

WyldKardAudioProcessorEditor::WyldKardAudioProcessorEditor (WyldKardAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // 1. Initialise and display the web browser
    addAndMakeVisible (webBrowser);

    // 2. Map C++ functions to be visible in JavaScript
    // This allows your React app to call window.juce.sendToNative(...)
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
                
                // Pass the command to the Audio Engine
                audioProcessor.previewSample (sampleName);
            }
        }
    });

    // 3. Set the URL for the frontend
    // Use localhost for development; switch to a local file for production
    webBrowser.goToURL ("http://localhost:5173"); 

    setSize (1000, 700);
}

WyldKardAudioProcessorEditor::~WyldKardAudioProcessorEditor()
{
}

void WyldKardAudioProcessorEditor::paint (juce::Graphics& g)
{
    // The web browser covers the whole area, but we can set a background color
    g.fillAll (juce::Colours::black);
}

void WyldKardAudioProcessorEditor::resized()
{
    // Ensure the browser fills the entire plugin window
    webBrowser.setBounds (getLocalBounds());
}
