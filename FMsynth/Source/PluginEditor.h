/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FmsynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FmsynthAudioProcessorEditor (FmsynthAudioProcessor&);
    ~FmsynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FmsynthAudioProcessor& audioProcessor;

    //Osc 1 labels
    juce::Label osc1Label;
    juce::Label osc1AttackLabel;
    juce::Label osc1DecayLabel;
    juce::Label osc1SustainLabel;
    juce::Label osc1ReleaseLabel;
    juce::Label osc1GainLabel;
    juce::Label osc1FreqLabel;
    juce::Label osc1ShapeLabel;

    //Osc 2 labels
    juce::Label osc2Label;
    juce::Label osc2AttackLabel;
    juce::Label osc2DecayLabel;
    juce::Label osc2SustainLabel;
    juce::Label osc2ReleaseLabel;
    juce::Label osc2GainLabel;
    juce::Label osc2FreqLabel;
    juce::Label osc2ModIndexLabel;
    juce::Label osc2ShapeLabel;

    //Osc 1 Sliders
    juce::Slider osc1AttackSlider;
    juce::Slider osc1DecaySlider;
    juce::Slider osc1SustainSlider;
    juce::Slider osc1ReleaseSlider;
    juce::Slider osc1GainSlider;
    juce::Slider osc1FreqSlider;
    juce::Slider osc1ShapeSlider;

    //Osc 2 Sliders
    juce::Slider osc2AttackSlider;
    juce::Slider osc2DecaySlider;
    juce::Slider osc2SustainSlider;
    juce::Slider osc2ReleaseSlider;
    juce::Slider osc2GainSlider;
    juce::Slider osc2FreqSlider;
    juce::Slider osc2ModIndexSlider;
    juce::Slider osc2ShapeSlider;

    //Osc 1 Slider attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc1AttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc1DecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc1SustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc1ReleaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc1GainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc1FreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc1ShapeAttachment;

    //Osc 2 Slider attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2AttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2DecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2SustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2ReleaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2GainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2FreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2ModIndexAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>  osc2ShapeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FmsynthAudioProcessorEditor)
};
