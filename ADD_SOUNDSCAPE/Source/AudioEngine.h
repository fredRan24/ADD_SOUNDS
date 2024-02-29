/*
  ==============================================================================

    AudioEngine.h
    Created: 28 Feb 2024 1:46:20pm
    Author:  Alfie Ransome

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SoundEffect.h"

class AudioEngine : public juce::AudioAppComponent
{
public:
    AudioEngine();
    ~AudioEngine() override;
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // Methods to control sound effects
    void playSoundEffect(const juce::String& effectName);
    void stopSoundEffect(const juce::String& effectName);
    void addSoundEffect(const juce::File& soundFile);
    void saveSoundEffects();
    void loadSoundEffects();
    void updateSoundEffectsList(const juce::File& file);

    // Methods for the 742Hz tone
    void start742HzTone();
    void stop742HzTone();
    void setVolume(float volume);
    
    juce::ValueTree soundEffectsTree;

private:
    juce::MixerAudioSource mixer;
    juce::AudioFormatManager formatManager;
    juce::dsp::Oscillator<float> oscillator{[](float x) { return std::sin(x); }};
    juce::dsp::Gain<float> gain; // Volume control
    bool tonePlaying = false; // To track the state of the 742Hz tone
    // Add a private member to AudioEngine to manage sound effects
    std::vector<std::unique_ptr<SoundEffect>> soundEffects; // Vector to manage sound effects
};
