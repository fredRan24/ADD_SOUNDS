/*
  ==============================================================================

    SoundEffect.h
    Created: 28 Feb 2024 1:46:35pm
    Author:  Alfie Ransome

  ==============================================================================
*/

// SoundEffect.h
#pragma once
#include <JuceHeader.h>

class SoundEffect {
public:
    SoundEffect(const juce::String& name, const juce::File& file); // Updated constructor
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void play(); // Ensuring this method is correctly named to match your call
    void stop();
    void setVolume(float newVolume);

    const juce::String& getName() const { return name; } // Getter for the effect's name

private:
    juce::String name; // Name of the sound effect
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    std::unique_ptr<juce::ResamplingAudioSource> resampleSource; // Using smart pointer for memory management
};
