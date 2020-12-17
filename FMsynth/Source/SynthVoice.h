/*
  ==============================================================================

    SynthVoice.h
    Created: 8 Nov 2020 6:42:10pm
    Author:  lengy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }


    //===============================================
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        osc1ADSR.noteOn();
        osc2ADSR.noteOn();
        level = velocity;
        auto Hz = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        osc1Frequency = Hz;
        osc2Frequency = Hz;
        juce::Logger::outputDebugString(std::to_string(osc1Frequency));
        juce::Logger::outputDebugString(std::to_string(osc2Frequency));
        juce::Logger::outputDebugString(std::to_string(osc1FreqRatio));
        juce::Logger::outputDebugString(std::to_string(osc2FreqRatio));

    }

    //===============================================
    void stopNote(float velocity, bool allowTailOff)
    {
        osc1ADSR.noteOff();
        osc2ADSR.noteOff();
        allowTailOff = true;

        clearCurrentNote();
    }

    //===============================================
    void pitchWheelMoved(int newPitchWheelValue)
    {

    }

    //===============================================
    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }


    float getCarrierFreq(float& modulator)
    {
        switch ((int)osc1Shape)
        {
        case 0:
            return osc1.sinewave(realFreq(osc1Frequency, osc1FreqRatio) + osc2ModIndex * modulator);
        case 1:
            return osc1.saw(realFreq(osc1Frequency, osc1FreqRatio) + osc2ModIndex * modulator);
        case 2:
            return osc1.square(realFreq(osc1Frequency, osc1FreqRatio) + osc2ModIndex * modulator);
        case 3:
            return osc1.triangle(realFreq(osc1Frequency, osc1FreqRatio) + osc2ModIndex * modulator);
        }
    }

    float getModulatorFreq()
    {
        switch ((int)osc2Shape)
        {
        case 0:
            return osc2.sinewave(realFreq(osc2Frequency, osc2FreqRatio));
        case 1:
            return osc2.saw(realFreq(osc2Frequency, osc2FreqRatio));
        case 2:
            return osc2.square(realFreq(osc2Frequency, osc2FreqRatio));
        case 3:
            return osc2.triangle(realFreq(osc2Frequency, osc2FreqRatio));
        }
    }

    float realFreq(float freq, float freqRatio)
    {
        return freq + freq * freqRatio;
    }

    //===============================================
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
    {
        osc1ADSR.setParameters(osc1ADSRParams);
        osc2ADSR.setParameters(osc2ADSRParams);

        for (int sample = 0; sample < numSamples; ++sample)
        {

            for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                auto modulator = getModulatorFreq();
                double sound = osc1Gain * osc1ADSR.getNextSample() * getCarrierFreq(modulator) + osc2Gain * osc2ADSR.getNextSample() * modulator;
                outputBuffer.addSample(channel, startSample, sound);
            }
            ++startSample;
        }
    }

    //===============================================
    void setOsc1ADSRSampleRate(double sampleRate) 
    {
        osc1ADSR.setSampleRate(sampleRate);
    }

    void setOsc2ADSRSampleRate(double sampleRate) 
    {
        osc2ADSR.setSampleRate(sampleRate);
    }
    

    void setOsc1Params(float* attack, float* decay, float* sustain, float* release, float* gain, float* freq, float* shape)
    {
        osc1ADSRParams.attack = *attack;
        osc1ADSRParams.decay = *decay;
        osc1ADSRParams.sustain = *sustain;
        osc1ADSRParams.release = *release;
        osc1Gain = *gain;
        osc1FreqRatio = *freq;
        osc1Shape = *shape;
    }
    void setOsc2Params(float* attack, float* decay, float* sustain, float* release, float* gain, float* freq, float* modindex, float* shape)
    {
        osc2ADSRParams.attack = *attack;
        osc2ADSRParams.decay = *decay;
        osc2ADSRParams.sustain = *sustain;
        osc2ADSRParams.release = *release;
        osc2Gain = *gain;
        osc2FreqRatio = *freq;
        osc2ModIndex = *modindex;
        osc2Shape = *shape;
    }

private:
    float osc1Gain;
    float osc1FreqRatio;
    float osc1Frequency;
    float osc1Shape;

    float osc2Gain;
    float osc2FreqRatio;
    float osc2Frequency;
    float osc2ModIndex;
    float osc2Shape;

    float level;

    maxiOsc osc1;
    maxiOsc osc2;

    juce::ADSR osc1ADSR;
    juce::ADSR osc2ADSR;

    juce::ADSR::Parameters osc1ADSRParams;
    juce::ADSR::Parameters osc2ADSRParams;
};
