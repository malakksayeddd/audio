#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"
//inheritance
class PlayerGUI : public juce::Component,  //byrsem 3la elscreen
    public juce::Button::Listener, //by3raf click el buttons
    public juce::Slider::Listener, //by3raf taghyor el buttons
    public juce::Timer, //timer l eltime w elwaves per sec
    public juce::ComboBox::Listener, //by3raf ta8yorat elcombobox
    public juce::ChangeListener //by3raf lma yt8air el soot
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate); //taghez el soot 2bl el tashgel
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill); //beygeb el soot ely hyshtaghl
    void releaseResources(); //clean resources b3d el enteha
    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override; 
    void timerCallback() override; //byshtagl kol shewaya l tagher eltime
    void changeListenerCallback(juce::ChangeBroadcaster* source) override; //bytab3 el changes
    void mouseDown(const juce::MouseEvent& event) override; //3shan ashab mn 3la waves
    void mouseDrag(const juce::MouseEvent& event) override;
private:
    PlayerAudio playerAudio; //byt3amel m3 kol haga btt3mel fel a8any

    // Buttons
    juce::TextButton loadButton{ "Load File" }, restartButton{ "Restart" },
        stopButton{ "Stop" }, muteButton{ "Mute" }, playButton{ "Play" },
        pauseButton{ "Pause" }, startButton{ "Go to Start" },
        endButton{ "Go to End" }, loopButton{ "Loop" }, addButton{ "Add File" };

    // Sliders & Labels
    juce::Slider volumeSlider, speedSlider, positionSlider;
    juce::Label positionLabel, metadataLabel;

    // Playlist
    juce::ComboBox playlistBox; //playlist feha kol el a8any el deftaha 
    std::vector<juce::File> playlistFiles; //playlist kol paths songs
    std::unique_ptr<juce::FileChooser> fileChooser; //select files mn elcomputer

    // Waveform
    juce::AudioFormatManager formatManager; //by2ra anwa3 el files
    juce::TextButton setAButton{ "Set A" }; //bdayat el goza el bytkrr
    juce::TextButton setBButton{ "Set B" }; //nehayat el goza el bytkrr
    juce::ToggleButton loopABButton{ "Loop A-B" }; //loop mn a to b
    bool fileLoaded = false, isLooping = false;
    juce::AudioThumbnailCache thumbnailCache{ 5 };    //to store the data mo2tan
    juce::AudioThumbnail thumbnail{ 512, playerAudio.getFormatManager(), thumbnailCache }; //byrsem shakl el waves

    void loadSelectedFile(int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};