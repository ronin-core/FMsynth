/*
  ==============================================================================

    SynthSound.h
    Created: 8 Nov 2020 6:42:04pm
    Author:  lengy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber)
    {
        return true;
    }
    
    bool appliesToChannel(int midiChannel)
    {
        return true;
    }
};