#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();

    
    resampleSource = std::make_unique<juce::ResamplingAudioSource>(&transportSource, false, 2); 
}

PlayerAudio::~PlayerAudio()
{
}
void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate); //audio source

    
    resampleSource->prepareToPlay(samplesPerBlockExpected, sampleRate); //samples we have everytime
}
void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource->getNextAudioBlock(bufferToFill); 
    if (loopSegment)
    {
        double current = transportSource.getCurrentPosition();
        if (current >= loopEnd)
            transportSource.setPosition(loopStart);
    }

}
void PlayerAudio::releaseResources()
{
    resampleSource->releaseResources(); 
}
bool PlayerAudio::loadFile(const juce::File& file)
{
    if (file.existsAsFile()) //check fe file
    {
        if (auto* reader = formatManager.createReaderFor(file)) //read with true value
        {

            transportSource.stop(); //stop 
            transportSource.setSource(nullptr); //
            readerSource.reset(); //delet ai old sourse

            //read new source
            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

            // new source with transport
            transportSource.setSource(readerSource.get(),
                0,
                nullptr,
                reader->sampleRate);

            //read metadatavalues
            title = reader->metadataValues.getValue("title", file.getFileName());
            artist = reader->metadataValues.getValue("artist", "Unknown Artist");
            album = reader->metadataValues.getValue("album", "Unknown Album");
            duration = reader->lengthInSamples / reader->sampleRate;

            transportSource.start(); //start
        }
    }
    return true; //all done yb2a true

}
void PlayerAudio::play()
{
    transportSource.start();
}
void PlayerAudio::stop()
{
    transportSource.stop();
}
void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}
void PlayerAudio::setPosition(double pos) {
    transportSource.setPosition(pos);
}
double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}
double PlayerAudio::getLength() const
{
    return transportSource.getLengthInSeconds();
}
void PlayerAudio::toggleMute()
{
    if (!isMuted)
    {
        lastV = transportSource.getGain();
        transportSource.setGain(0.0f);
        isMuted = true;
    }
    else
    {
        transportSource.setGain(lastV);
        isMuted = false;
    }
}
void PlayerAudio::pause()
{
    transportSource.stop();
}
double PlayerAudio::getLengthInSeconds() const
{
    return transportSource.getLengthInSeconds();
}
void PlayerAudio::goToStart()
{
    transportSource.setPosition(0.0);
}
void PlayerAudio::goToEnd()
{
    auto len = transportSource.getLengthInSeconds();
    transportSource.setPosition(len);
}
void PlayerAudio::setLooping(bool shouldLoop)
{
    if (readerSource)
        readerSource->setLooping(shouldLoop);
}
void PlayerAudio::setSpeed(double newSpeed) 
{
    if (resampleSource)
        resampleSource->setResamplingRatio(newSpeed);
}
void PlayerAudio::setLoopPoints(double start, double end)
{
    loopStart = start;
    loopEnd = end;
}

void PlayerAudio::enableLoop(bool shouldLoop)
{
    loopSegment = shouldLoop;
}

double PlayerAudio::getLoopStart() const
{
    return loopStart;
}

double PlayerAudio::getLoopEnd() const
{
    return loopEnd;
}
void PlayerAudio::setLoopSegmentEnabled(bool shouldLoop)
{
    loopSegment = shouldLoop;
}