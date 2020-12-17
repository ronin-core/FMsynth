/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FmsynthAudioProcessor::FmsynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), osc1Params(*this, nullptr, "Osc1 Parameters", createOsc1Parameters()),
                          osc2Params(*this, nullptr, "Osc2 Parameters", createOsc2Parameters())
#endif
{
    fmSynth.clearVoices();

    for (int voice = 0; voice < 5; voice++) 
    {
        fmSynth.addVoice(new SynthVoice());
    }

    fmSynth.clearSounds();
    fmSynth.addSound(new SynthSound());

}

FmsynthAudioProcessor::~FmsynthAudioProcessor()
{
}

//==============================================================================
const juce::String FmsynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FmsynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FmsynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FmsynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FmsynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FmsynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FmsynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FmsynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FmsynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void FmsynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FmsynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    fmSynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void FmsynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FmsynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FmsynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < fmSynth.getNumVoices(); i++)
    {
        if (fmVoice = dynamic_cast<SynthVoice*>(fmSynth.getVoice(i)))
        {
            fmVoice->setOsc1ADSRSampleRate(lastSampleRate);
            fmVoice->setOsc2ADSRSampleRate(lastSampleRate);

            auto osc1Attack = (float*)osc1Params.getRawParameterValue("1ATTACK");
            auto osc1Decay = (float*)osc1Params.getRawParameterValue("1DECAY");
            auto osc1Sustain = (float*)osc1Params.getRawParameterValue("1SUSTAIN");
            auto osc1Release = (float*)osc1Params.getRawParameterValue("1RELEASE");
            auto osc1Gain = (float*)osc1Params.getRawParameterValue("1GAIN");
            auto osc1Freq = (float*)osc1Params.getRawParameterValue("1FREQ");
            auto osc1Shape = (float*)osc1Params.getRawParameterValue("1SHAPE");

            fmVoice->setOsc1Params(osc1Attack, osc1Decay, osc1Sustain, osc1Release, osc1Gain, osc1Freq, osc1Shape);
            
            auto osc2Attack = (float*)osc2Params.getRawParameterValue("2ATTACK");
            auto osc2Decay = (float*)osc2Params.getRawParameterValue("2DECAY");
            auto osc2Sustain = (float*)osc2Params.getRawParameterValue("2SUSTAIN");
            auto osc2Release = (float*)osc2Params.getRawParameterValue("2RELEASE");
            auto osc2Gain = (float*)osc2Params.getRawParameterValue("2GAIN");
            auto osc2Freq = (float*)osc2Params.getRawParameterValue("2FREQ");
            auto osc2ModIndex = (float*)osc2Params.getRawParameterValue("2MOD");
            auto osc2Shape = (float*)osc2Params.getRawParameterValue("2SHAPE");

            fmVoice->setOsc2Params(osc2Attack, osc2Decay, osc2Sustain, osc2Release, osc2Gain, osc2Freq, osc2ModIndex, osc2Shape);
        }
    }

    fmSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool FmsynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FmsynthAudioProcessor::createEditor()
{
    return new FmsynthAudioProcessorEditor (*this);
}

//==============================================================================
void FmsynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FmsynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FmsynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FmsynthAudioProcessor::createOsc1Parameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    auto shapeRange = juce::NormalisableRange<float>(0, 3, 1);

    params.push_back(std::make_unique<juce::AudioParameterFloat>("1ATTACK", "Attack", 0.01f, 8.0f, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("1DECAY", "Decay", 0.01f, 4.0f, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("1SUSTAIN", "Sustain", 0.0f, 1.0f, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("1RELEASE", "Release", 0.01f, 4.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("1GAIN", "Gain", 0.0f, 1.0f, 0.7f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("1FREQ", "Frequency", -0.9999f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("1SHAPE", "Wave shape", shapeRange, 0));


    return { params.begin(), params.end() };
}

juce::AudioProcessorValueTreeState::ParameterLayout FmsynthAudioProcessor::createOsc2Parameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    auto shapeRange = juce::NormalisableRange<float>(0, 3, 1);

    params.push_back(std::make_unique<juce::AudioParameterFloat>("2ATTACK", "Attack", 0.01f, 8.0f, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("2DECAY", "Decay", 0.01f, 4.0f, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("2SUSTAIN", "Sustain", 0.0f, 1.0f, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("2RELEASE", "Release", 0.01f, 4.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("2GAIN", "Gain", 0.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("2FREQ", "Frequency", -0.9999f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("2MOD", "Mod Index", 0.0f, 1500.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("2SHAPE", "Wave shape", shapeRange, 0));

    return { params.begin(), params.end() };
}

