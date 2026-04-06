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
    webBrowser.addNativeFunction ("sendToNative", [this] (const juce::var& args) {
        if (args.isArray()) {
            auto message = args[0].toString();
            // Logic to pass data to your AudioProcessor
            // e.g., audioProcessor.loadSample(message);
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
