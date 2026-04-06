#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class WyldKardAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    WyldKardAudioProcessorEditor (WyldKardAudioProcessor&);
    ~WyldKardAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This component hosts your React/Vite app
    juce::WebBrowserComponent webBrowser;

    // Helper to register functions the JS side can call
    void setupWebInteractions();

    WyldKardAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WyldKardAudioProcessorEditor)
};
