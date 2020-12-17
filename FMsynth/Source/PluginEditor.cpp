/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FmsynthAudioProcessorEditor::FmsynthAudioProcessorEditor (FmsynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{   
    //OSC 1
    osc1AttackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc1AttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc1AttackSlider.setTooltip(juce::String("Osc1 Attack"));
    osc1DecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc1DecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc1DecaySlider.setTooltip(juce::String("Osc1 Decay"));
    osc1SustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc1SustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc1SustainSlider.setTooltip(juce::String("Osc1 Sustain"));
    osc1ReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc1ReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc1ReleaseSlider.setTooltip(juce::String("Osc1 Release"));
    osc1GainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc1GainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc1GainSlider.setTooltip(juce::String("Osc1 Gain"));
    osc1FreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc1FreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc1FreqSlider.setTooltip(juce::String("Osc1 Freq"));
    osc1ShapeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc1ShapeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc1ShapeSlider.setTooltip(juce::String("Osc1 Shape"));

    osc1Label.setText("Carrier: Osc1", juce::dontSendNotification);
    osc1AttackLabel.setText("Att", juce::dontSendNotification);
    osc1AttackLabel.attachToComponent(&osc1AttackSlider, false);
    osc1DecayLabel.setText("Dec", juce::dontSendNotification);
    osc1DecayLabel.attachToComponent(&osc1DecaySlider, false);
    osc1SustainLabel.setText("Sus", juce::dontSendNotification);
    osc1SustainLabel.attachToComponent(&osc1SustainSlider, false);
    osc1ReleaseLabel.setText("Rel", juce::dontSendNotification);
    osc1ReleaseLabel.attachToComponent(&osc1ReleaseSlider, false);
    osc1GainLabel.setText("Gain", juce::dontSendNotification);
    osc1GainLabel.attachToComponent(&osc1GainSlider, false);
    osc1FreqLabel.setText("Freq", juce::dontSendNotification);
    osc1FreqLabel.attachToComponent(&osc1FreqSlider, false);
    osc1ShapeLabel.setText("Shape", juce::dontSendNotification);
    osc1ShapeLabel.attachToComponent(&osc1ShapeSlider, true);

    addAndMakeVisible(osc1Label);
    addAndMakeVisible(osc1AttackLabel);
    addAndMakeVisible(osc1DecayLabel);
    addAndMakeVisible(osc1SustainLabel);
    addAndMakeVisible(osc1ReleaseLabel);
    addAndMakeVisible(osc1GainLabel);
    addAndMakeVisible(osc1FreqLabel);
    addAndMakeVisible(osc1ShapeLabel);

    addAndMakeVisible(osc1AttackSlider);
    addAndMakeVisible(osc1DecaySlider);
    addAndMakeVisible(osc1SustainSlider);
    addAndMakeVisible(osc1ReleaseSlider);
    addAndMakeVisible(osc1GainSlider);
    addAndMakeVisible(osc1FreqSlider);
    addAndMakeVisible(osc1ShapeSlider);

    osc1AttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc1Params, "1ATTACK", osc1AttackSlider);
    osc1DecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc1Params, "1DECAY", osc1DecaySlider);
    osc1SustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc1Params, "1SUSTAIN", osc1SustainSlider);
    osc1ReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc1Params, "1RELEASE", osc1ReleaseSlider);
    osc1GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc1Params, "1GAIN", osc1GainSlider);
    osc1FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc1Params, "1FREQ", osc1FreqSlider);
    osc1ShapeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc1Params, "1SHAPE", osc1ShapeSlider);

    //OSC 2
    osc2AttackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2AttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2AttackSlider.setTooltip(juce::String("Osc1 Attack"));
    osc2DecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2DecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2DecaySlider.setTooltip(juce::String("Osc1 Decay"));
    osc2SustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2SustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2SustainSlider.setTooltip(juce::String("Osc1 Sustain"));
    osc2ReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2ReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2ReleaseSlider.setTooltip(juce::String("Osc1 Release"));
    osc2GainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2GainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2GainSlider.setTooltip(juce::String("Osc1 Gain"));
    osc2FreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2FreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2FreqSlider.setTooltip(juce::String("Osc1 Freq"));
    osc2ModIndexSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    osc2ModIndexSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2ModIndexSlider.setTooltip(juce::String("Osc1 Mod Index"));
    osc2ShapeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc2ShapeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    osc2ShapeSlider.setTooltip(juce::String("Osc2 Shape"));

    osc2Label.setText("Modulator: Osc2", juce::dontSendNotification);
    osc2AttackLabel.setText("Att", juce::dontSendNotification);
    osc2AttackLabel.attachToComponent(&osc2AttackSlider, false);
    osc2DecayLabel.setText("Dec", juce::dontSendNotification);
    osc2DecayLabel.attachToComponent(&osc2DecaySlider, false);
    osc2SustainLabel.setText("Sus", juce::dontSendNotification);
    osc2SustainLabel.attachToComponent(&osc2SustainSlider, false);
    osc2ReleaseLabel.setText("Rel", juce::dontSendNotification);
    osc2ReleaseLabel.attachToComponent(&osc2ReleaseSlider, false);
    osc2GainLabel.setText("Gain", juce::dontSendNotification);
    osc2GainLabel.attachToComponent(&osc2GainSlider, false);
    osc2FreqLabel.setText("Freq", juce::dontSendNotification);
    osc2FreqLabel.attachToComponent(&osc2FreqSlider, false);
    osc2ModIndexLabel.setText("FM", juce::dontSendNotification);
    osc2ModIndexLabel.attachToComponent(&osc2ModIndexSlider, false);
    osc2ShapeLabel.setText("Shape", juce::dontSendNotification);
    osc2ShapeLabel.attachToComponent(&osc2ShapeSlider, true);

    addAndMakeVisible(osc2Label);
    addAndMakeVisible(osc2AttackLabel);
    addAndMakeVisible(osc2DecayLabel);
    addAndMakeVisible(osc2SustainLabel);
    addAndMakeVisible(osc2ReleaseLabel);
    addAndMakeVisible(osc2GainLabel);
    addAndMakeVisible(osc2FreqLabel);
    addAndMakeVisible(osc2ShapeLabel);

    addAndMakeVisible(osc2AttackSlider);
    addAndMakeVisible(osc2DecaySlider);
    addAndMakeVisible(osc2SustainSlider);
    addAndMakeVisible(osc2ReleaseSlider);
    addAndMakeVisible(osc2GainSlider);
    addAndMakeVisible(osc2FreqSlider);
    addAndMakeVisible(osc2ModIndexSlider);
    addAndMakeVisible(osc2ShapeSlider);

    osc2AttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2ATTACK", osc2AttackSlider);
    osc2DecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2DECAY", osc2DecaySlider);
    osc2SustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2SUSTAIN", osc2SustainSlider);
    osc2ReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2RELEASE", osc2ReleaseSlider);
    osc2GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2GAIN", osc2GainSlider);
    osc2FreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2FREQ", osc2FreqSlider);
    osc2ModIndexAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2MOD", osc2ModIndexSlider);
    osc2ShapeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.osc2Params, "2SHAPE", osc2ShapeSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (580, 300);
}

FmsynthAudioProcessorEditor::~FmsynthAudioProcessorEditor()
{
}

//==============================================================================
void FmsynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void FmsynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    osc1Label.setBounds(90, 10, 200, 90);
    osc1AttackSlider.setBounds(10, 90, 40, 200);
    osc1DecaySlider.setBounds(50, 90, 40, 200);
    osc1SustainSlider.setBounds(90, 90, 40, 200);
    osc1ReleaseSlider.setBounds(130, 90, 40, 200);
    osc1GainSlider.setBounds(170, 90, 40, 200);
    osc1FreqSlider.setBounds(210, 90, 40, 200);
    osc1ShapeSlider.setBounds(190, 0, 60, 60);
    
    osc2Label.setBounds(380, 10, 200, 90);
    osc2AttackSlider.setBounds(300, 90, 40, 200);
    osc2DecaySlider.setBounds(340, 90, 40, 200);
    osc2SustainSlider.setBounds(380, 90, 40, 200);
    osc2ReleaseSlider.setBounds(420, 90, 40, 200);
    osc2GainSlider.setBounds(460, 90, 40, 200);
    osc2FreqSlider.setBounds(500, 90, 40, 200);
    osc2ModIndexSlider.setBounds(540, 90, 40, 200);
    osc2ShapeSlider.setBounds(520, 0, 60, 60);
}
