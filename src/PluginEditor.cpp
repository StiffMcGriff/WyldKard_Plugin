#include "PluginProcessor.h"
#include "PluginEditor.h"

WyldKardAudioProcessorEditor::WyldKardAudioProcessorEditor (WyldKardAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // 1. Initialise the web browser
    addAndMakeVisible (webBrowser);

    // 2. Map C++ functions to be visible in JavaScript
    // In React, you'll call: window.juce.postMessage({ action: 'loadSample', path: '...' })
    webBrowser.addResourceProvider ([this](const juce::String& url) {
        // Handle local file routing or asset loading here if needed
        return std::nullopt;
    });

    // 3. Register a native callback
    // Inside WyldKardAudioProcessorEditor constructor
webBrowser.addNativeFunction ("sendToNative", [this] (const juce::var& args) 
{
    if (args.isArray() && args.size() > 0) 
    {
        auto jsonString = args[0].toString();
        auto var = juce::JSON::parse(jsonString);
        
        if (var.getProperty("action", "").toString() == "PLAY_SAMPLE")
        {
            auto sampleName = var.getProperty("payload", "").getProperty("name", "").toString();
            DBG("JUCE: User wants to play " << sampleName);
            
            // Call a function in your Processor to trigger the audio
            // audioProcessor.previewSample(sampleName);
        }
    }
});

    // 4. Load your Vite dev server URL
    // Switch this to a local resource for production builds
    webBrowser.goToURL ("http://localhost:5173"); 

    setSize (800, 600);
}

void WyldKardAudioProcessorEditor::resized()
{
    webBrowser.setBounds (getLocalBounds());
}
