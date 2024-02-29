/*
  ==============================================================================

    AudioEngine.cpp
    Created: 28 Feb 2024 1:46:20pm
    Author:  Alfie Ransome

  ==============================================================================
*/

#include "AudioEngine.h"
#include "SoundEffect.h"

AudioEngine::AudioEngine() : soundEffectsTree("SoundEffects") {
    formatManager.registerBasicFormats();
    oscillator.initialise([](float x) { return std::sin(x); }, 128);
    setAudioChannels(0, 2); // No inputs, two outputs (stereo)
}
AudioEngine::~AudioEngine() {
    shutdownAudio(); // Ensure to properly shut down the audio device
}


void AudioEngine::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlockExpected;
    spec.sampleRate = sampleRate;
    spec.numChannels = 2; // You set this when calling setAudioChannels(0, 2), so it's known.

    oscillator.prepare(spec);
    gain.prepare(spec);

    oscillator.setFrequency(742.0f, true);
    gain.setGainLinear(0.1f); // Start with a default low volume
}


void AudioEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    bufferToFill.clearActiveBufferRegion();

    if (tonePlaying) {
        juce::dsp::AudioBlock<float> block(*bufferToFill.buffer);
        block = block.getSubBlock((size_t)bufferToFill.startSample, (size_t)bufferToFill.numSamples);

        juce::dsp::ProcessContextReplacing<float> context(block);
        oscillator.process(context);
        gain.process(context);
    }
}

void AudioEngine::releaseResources() {
    // Cleanup if necessary
}

void AudioEngine::start742HzTone() {
    tonePlaying = true;
}

void AudioEngine::stop742HzTone() {
    tonePlaying = false;
}

void AudioEngine::setVolume(float volume) {
    // Ensure volume is in a reasonable range [0.0, 1.0]
    gain.setGainLinear(volume);
}


void AudioEngine::playSoundEffect(const juce::String& effectName) {
    for (auto& effect : soundEffects) {
            if (effect->getName() == effectName) {
                effect->play();
                break; // Stop searching after finding and playing the effect
            }
        }
}


void AudioEngine::addSoundEffect(const juce::File& soundFile) {
    // Assume each sound file's name is unique and used as the effect's identifier
    auto name = soundFile.getFileNameWithoutExtension();
    auto newEffect = std::make_unique<SoundEffect>(name, soundFile);
    soundEffects.push_back(std::move(newEffect));
}

void AudioEngine::saveSoundEffects() {
    juce::File file("path/to/soundEffects.xml");
    std::unique_ptr<juce::XmlElement> xml(soundEffectsTree.createXml());
    xml->writeTo(file, {});
}

void AudioEngine::loadSoundEffects() {
    juce::File file("path/to/soundEffects.xml");
    std::unique_ptr<juce::XmlElement> xmlElement(juce::XmlDocument::parse(file));
    if (xmlElement) {
        soundEffectsTree = juce::ValueTree::fromXml(*xmlElement);
        // Reconstruct sound effects from the tree
        for (auto effect : soundEffectsTree) {
            juce::File effectFile(effect.getProperty("path").toString());
            addSoundEffect(effectFile);
        }
    }
}

void AudioEngine::updateSoundEffectsList(const juce::File& file) {
    auto newEffect = juce::ValueTree("Effect");
    newEffect.setProperty("name", file.getFileNameWithoutExtension(), nullptr);
    newEffect.setProperty("path", file.getFullPathName(), nullptr);
    soundEffectsTree.addChild(newEffect, -1, nullptr);

    saveSoundEffects(); // Save the updated list to file
}
