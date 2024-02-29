// SoundEffect.cpp
#include "SoundEffect.h"

SoundEffect::SoundEffect(const juce::File& file) {
    formatManager.registerBasicFormats(); // Register the basic audio formats
    auto* reader = formatManager.createReaderFor(file); // Create a reader for the audio file

    if (reader != nullptr) {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release()); // Take ownership of the source
    }
}

void SoundEffect::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    if (resampleSource != nullptr) {
        delete resampleSource;
    }
    resampleSource = new juce::ResamplingAudioSource(&transportSource, false, 2);
    resampleSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void SoundEffect::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    if (transportSource.isPlaying()) {
        resampleSource->getNextAudioBlock(bufferToFill);
    } else {
        bufferToFill.clearActiveBufferRegion();
    }
}

void SoundEffect::start() {
    transportSource.start();
}

void SoundEffect::stop() {
    transportSource.stop();
}

void SoundEffect::setVolume(float newVolume) {
    transportSource.setGain(newVolume);
}
