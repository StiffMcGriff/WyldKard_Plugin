#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class WyldKardAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WyldKardAudioProcessorEditor (WyldKardAudioProcessor&);
    ~WyldKardAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This component hosts your React/Vite frontend
    juce::WebBrowserComponent webBrowser;

    // This reference is our link to the audio engine
    WyldKardAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WyldKardAudioProcessorEditor)
};
