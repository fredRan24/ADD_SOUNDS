#pragma once

#include <JuceHeader.h>
#include "AudioEngine.h"

class MainComponent   : public juce::Component,
                        public juce::Button::Listener,
                        public juce::Slider::Listener // Add Slider listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override; // Implement slider listener
    void addSoundEffect();

private:
    juce::TextButton addButton; // Existing Add Sound button
    juce::TextButton playButton; // Play button
    juce::TextButton stopButton; // Stop button
    juce::TextButton addEffectButton{"Add Sound Effect"};
    juce::Slider volumeSlider; // Volume slider for the sine wave
    std::unique_ptr<AudioEngine> audioEngine;
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
