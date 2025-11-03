#pragma once
#include <JuceHeader.h>

class PlayerAudio 
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate); //functions assasia mn code el dr
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill); //the same
    void releaseResources(); //the same
    bool loadFile(const juce::File& file);
    void play();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;
    void toggleMute();
    bool isMuted = false;
    float lastV = 0.5f;
    double getLengthInSeconds() const;
    void pause();
    void goToStart();
    void goToEnd();
    void setLooping(bool shouldLoop);
    void setLoopPoints(double start, double end);
    void enableLoop(bool shouldLoop);
    double getLoopStart() const;
    double getLoopEnd() const;
    void setLoopSegmentEnabled(bool shouldLoop);
    bool isLoopSegmentEnabled() const { return loopSegment; }


    juce::String getTitle() const { return title; }
    juce::String getArtist() const { return artist; }
    juce::String getAlbum() const { return album; }
    double getDuration() const { return duration; }

    void setSpeed(double newSpeed);
    juce::AudioFormatManager& getFormatManager() { return formatManager; } //anwa3 el loaad files

private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource; 
    juce::String title;
    juce::String artist;
    juce::String album;
    double duration = 0.0;
    bool loopSegment = false;
    double loopStart = 0.0;
    double loopEnd = 0.0;

    std::unique_ptr<juce::ResamplingAudioSource> resampleSource;
};