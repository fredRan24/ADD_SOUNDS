#include "AudioEngine.h"
#include "SoundEffect.h"

AudioEngine::AudioEngine() {
    formatManager.registerBasicFormats(); // Register formats to enable reading different audio file types
    setAudioChannels(0, 2); // no inputs, two outputs (stereo)
}

AudioEngine::~AudioEngine() {
    shutdownAudio(); // Ensure to properly shut down the audio device
}

void AudioEngine::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    // Initialize your audio sources here. For now, let's keep it simple.
}

void AudioEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    bufferToFill.clearActiveBufferRegion(); // Clear the buffer to avoid playing garbage/noise

    // Here, you would mix in the audio from your sound effects.
    // This could involve iterating over a collection of playing sound effects and adding their audio to the buffer.
}

void AudioEngine::releaseResources() {
    // Release any allocated resources.
}

void AudioEngine::playSoundEffect(const juce::String& effectName) {
    // For demonstration, let's assume you have a method to find a SoundEffect by name.
    // This is a placeholder for logic to play a specific sound effect.
    auto* effect = findSoundEffectByName(effectName);
    if (effect != nullptr) {
        effect->start(); // Assuming SoundEffect has a method to start playback
    }
}

// Placeholder for a method to find a SoundEffect instance by name
SoundEffect* AudioEngine::findSoundEffectByName(const juce::String& name) {
    // Implementation depends on how you store/manage SoundEffect instances.
    return nullptr; // Placeholder implementation
}
