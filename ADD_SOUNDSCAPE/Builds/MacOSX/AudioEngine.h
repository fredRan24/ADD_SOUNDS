#pragma once
#include <JuceHeader.h>

class AudioEngine : public juce::AudioAppComponent
{
public:
    AudioEngine();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // Methods to control sound effects
    void playSoundEffect(const juce::String& effectName);
    void stopSoundEffect(const juce::String& effectName);
    void addSoundEffect(const juce::File& soundFile);

    // Methods for the 742Hz tone
    void start742HzTone();
    void stop742HzTone();

private:
    juce::MixerAudioSource mixer; // Mixes multiple audio sources together
    // Add more members as needed for managing sound effects and the 742Hz tone
};
