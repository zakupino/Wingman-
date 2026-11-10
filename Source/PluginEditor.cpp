#include "PluginProcessor.h"
#include "PluginEditor.h"

WingmanStyleAnalyzerAudioProcessorEditor::WingmanStyleAnalyzerAudioProcessorEditor (WingmanStyleAnalyzerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // কাস্টম লুক অ্যান্ড ফিল অ্যাপ্লাই করা
    setStyle(&customLookAndFeel);

    // কাটঅফ নোব কনফিগারেশন
    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(cutoffSlider);

    cutoffLabel.setText("FILTER CUTOFF", juce::dontSendNotification);
    cutoffLabel.setJustificationType(juce::Justification::centred);
    cutoffLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    addAndMakeVisible(cutoffLabel);

    // উইন্ডোর সাইজ নির্ধারণ (যেমন: 600x400 পিক্সেল)
    setSize (600, 400);
}

WingmanStyleAnalyzerAudioProcessorEditor::~WingmanStyleAnalyzerAudioProcessorEditor()
{
    setStyle(nullptr);
}

void WingmanStyleAnalyzerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // উইন্ডোজের ডার্ক চারকোল ব্যাকগ্রাউন্ড (Wingman স্টাইল)
    g.fillAll (juce::Colour(0xff121216));

    // হেডার টাইটেল ড্রয়িং
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("WINGMAN STYLE ANALYZER", 20, 20, 300, 30, juce::Justification::left);

    // সাবটাইল বা অ্যাকসেন্ট লাইন
    g.setColour (juce::Colours::cyan.withAlpha(0.5f));
    g.drawHorizontalLine(60, 20.0f, (float)getWidth() - 20.0f);
}

void WingmanStyleAnalyzerAudioProcessorEditor::resized()
{
    // কন্ট্রোল কম্পোনেন্টগুলোর পজিশন
    cutoffSlider.setBounds(50, 100, 100, 120);
    cutoffLabel.setBounds(40, 220, 120, 20);
}