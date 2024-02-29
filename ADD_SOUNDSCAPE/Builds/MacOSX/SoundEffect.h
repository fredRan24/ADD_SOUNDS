// SoundEffect.h
#pragma once
#include <JuceHeader.h>

class SoundEffect {
public:
    SoundEffect(const juce::File& file);
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void start();
    void stop();
    void setVolume(float newVolume);

private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource* resampleSource = nullptr; // For sample rate adjustment
};
