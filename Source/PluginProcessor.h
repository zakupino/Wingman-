#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

// কাস্টম লুক এবং নিয়ন স্টাইল রোটারি নোব ডিজাইন
class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        // নিয়ন ব্লু এবং পার্পল কালার প্যালেট
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::cyan);
        setColour(juce::Slider::thumbColourId, juce::Colours::white);
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xff2a2d34));
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, const float rotaryStartAngle,
                          const float rotaryEndAngle, juce::Slider& slider) override
    {
        auto bounds = juce::Rectangle<float>(x, y, width, height).reduced(10.0f);
        auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto center = bounds.getCentre();
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // আউটার ব্যাকগ্রাউন্ড রিং
        g.setColour(findColour(juce::Slider::rotarySliderOutlineColourId));
        g.drawEllipse(center.x - radius, center.y - radius, radius * 2.0f, radius * 2.0f, 4.0f);

        // একটিভ আর্ক (ভ্যালু ফিল)
        juce::Path arcPath;
        arcPath.addCentredArc(center.x, center.y, radius, radius, 0.0f, rotaryStartAngle, angle, true);
        g.setColour(findColour(juce::Slider::rotarySliderFillColourId));
        g.strokePath(arcPath, juce::PathStrokeType(4.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        // সেন্টার নোব বডি
        juce::Path p;
        auto thumbWidth = radius * 0.2f;
        p.addRectangle(-thumbWidth * 0.5f, -radius + 8.0f, thumbWidth, radius * 0.5f);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(center));
        
        g.setColour(findColour(juce::Slider::thumbColourId));
        g.fillPath(p);
    }
};

class WingmanStyleAnalyzerAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    WingmanStyleAnalyzerAudioProcessorEditor (WingmanStyleAnalyzerAudioProcessor&);
    ~WingmanStyleAnalyzerAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    WingmanStyleAnalyzerAudioProcessor& audioProcessor;

    CustomLookAndFeel customLookAndFeel;
    juce::Slider cutoffSlider;
    juce::Label cutoffLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WingmanStyleAnalyzerAudioProcessorEditor)
};