#include "MainComponent.h"

MainComponent::MainComponent()
    : addButton("Add Sound"), playButton("Play"), stopButton("Stop")
{
    // Existing setup for addButton
    // Setup play button
    playButton.addListener(this);
    addAndMakeVisible(playButton);

    // Setup stop button
    stopButton.addListener(this);
    addAndMakeVisible(stopButton);

    // Setup volume slider
    volumeSlider.setRange(0.0, 1.0); // Assuming volume range from 0 (mute) to 1 (max)
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);
    
    addEffectButton.onClick = [this] { addSoundEffect(); };
    addAndMakeVisible(addEffectButton);

    audioEngine = std::make_unique<AudioEngine>();
    setSize(600, 200); // Adjust size as necessary
}


MainComponent::~MainComponent()
{
    addButton.removeListener(this);
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey); // Clear the background
}

void MainComponent::resized()
{
    auto area = getLocalBounds().reduced(10); // Reduce the main area slightly for padding

    // Calculate the heights dynamically based on the total available area
    int totalControls = 4; // Update this if you add more controls
    int controlHeight = (area.getHeight() / totalControls) - (10 * (totalControls - 1) / totalControls); // Dynamic height calculation

    // Set bounds for each control, distributing them vertically
    playButton.setBounds(area.removeFromTop(controlHeight));
    area.removeFromTop(10); // Add some space between controls

    stopButton.setBounds(area.removeFromTop(controlHeight));
    area.removeFromTop(10); // Add some space between controls

    addEffectButton.setBounds(area.removeFromTop(controlHeight));
    area.removeFromTop(10); // Add some space between controls

    volumeSlider.setBounds(area.removeFromTop(controlHeight)); // The slider takes the remaining space
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        audioEngine->start742HzTone();
    }
    else if (button == &stopButton)
    {
        audioEngine->stop742HzTone();
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        audioEngine->setVolume(volumeSlider.getValue());
    }
}

void MainComponent::addSoundEffect() {
    DBG("Add sound effect button clicked");
    fileChooser = std::make_unique<juce::FileChooser>("Select a sound effect file...",
                                                      juce::File::getSpecialLocation
                                                      (juce::File::userHomeDirectory),
                                                      "*.wav;*.mp3;*.aiff", false);
    
    constexpr auto fileChooserFlags =   juce::FileBrowserComponent::openMode |
                                        juce::FileBrowserComponent::canSelectFiles;
    
    fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser) {
        const juce::File chosenFile(chooser.getResult());
        DBG("Chosen file was: " + chosenFile.getFullPathName());
        this->audioEngine->addSoundEffect(chosenFile);
    });
}
