/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OtherLookAndFeel.h"
#include <iostream>
#include <fstream>

//==============================================================================
/**
*/
class NewObliqueFilterAudioProcessorEditor  :
public AudioProcessorEditor, private ComboBox::Listener, private Button::Listener
{
public:
    NewObliqueFilterAudioProcessorEditor (NewObliqueFilterAudioProcessor&);
    ~NewObliqueFilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox*) override;
    
private:
    void addTextToConcrete()
    {
        concreteLabels.add("What do filters do?");
        concreteTexts.add("A filter is an effect which can emphasize and eliminate frequencies from a sound signal. They are used to alter the harmonic content of a sound.");
        
        concreteLabels.add("The low-pass filter");
        concreteTexts.add("The low-pass filter attenuates frequencies below the given cut-off point. It can be used to make room in your track for high-end elements by adding it to parts of your track that don't need their low end frequencies such as hi-hats.");
        
        concreteLabels.add("The high-pass filter");
        concreteTexts.add("The high-pass filter attenuates frequencies above the given cut-off point. It can be used to make room in your track for low-end elements such as kick drums and bass-lines by adding it to parts of your track that don't need their high end frequencies.");
        
        concreteLabels.add("The bandpass filter");
        concreteTexts.add("A bandpass filter is like a combination of a high-pass and a low-pass filter; it allows only frequencies within a certain frequency 'band' to pass through the output. The cut-off parameter works slightly differently on a band-pass filter - it determines the centre of the band that is passed through the filter. Use this to allow narrow frequency bands to pass through, and for extreme harmonic shaping");
        
        concreteLabels.add("The Cut-off Parameter");
        concreteTexts.add("This parameter sets the point on the frequency spectrum where the filter begins to attenuate the sound. For low-pass filters, anything above the value given will be attenuated, while for high-pass filters, anything below the value set will be attenuated.");
        
        concreteLabels.add("The Q Parameter");
        concreteTexts.add("This parameter also changes depending on whether the filter is in bandpass or high/low-pass mode. In a bandpass filter, a higher Q corresponds to a narrower pass band, while in a low or high passs filter, a higher Q creates an emphasis (boosted signal) at just above or below the cutoff frequency repsecitvely.");
        
        concreteLabels.add("The Peak Gain Parameter");
        concreteTexts.add("This parameter changes the ratio between the volume at the input and the volume at the output of the filter peak. Where this filter peak is on the frequency spectrum is abstracted away from you, but essentially this can be used to either accentuate or attenuate the sound's peak (which, when used in conjunction with the Q paramater, usually refers to the peak created by increasing the Q). ");
        
        concreteLabels.add("The notch filter (or band stop)");
        concreteTexts.add("The notch filter is effectively the inverse of a bandpass filter; it allows only frequencies outside a certain frequency 'band' to pass through to the output. The cut-off parameter works just like a band-pass filter, determining the centre of the band that is notched out of the sound signal. This can be used to generate subtle tonal movement in track elements, especially when automated.");
        
        concreteLabels.add("The peak filter");
        concreteTexts.add("In brief, a peak filter is a very narrow band pass filter, and is usually used in other specific types of effects, like wah-wah pedals. These can be used creatively on their own");
        
        concreteLabels.add("The low-shelf filter");
        concreteTexts.add("A low-shelf filter serves a similar purpose to a high-pass filter - it cuts frequencies below the set cut-off frequency, but with one key difference; instead of entirely removing these frequencies, it reduces the volume such that a reduced proportion of those frequenies still pass through the output.");
        
        concreteLabels.add("The high-shelf filter");
        concreteTexts.add("A high-shelf filter serves a similar purpose to a low-pass filter - it cuts frequencies above the set cut-off frequency, but instead of entirely removing the cut frequencies, it reduces the volume such that a reduced proportion of those frequencies still pass through the output.");
        
        concreteLabels.add("Automating the cut-off");
        concreteTexts.add("Cut-off automation (changing the dial over time) is an extemely common practice in sound-design. It allows you to morph the timbre (or harmonic quality) of the sound over time. Depending on which filter type you use, this will have a unique effect. With high-pass and low-pass filters, automating the cut-off has an extreme effect on the timbre - try this on a pad or atmospheric element in your track. On the other hand, using a notch or peak filter will have a more subtle effect and can be used to add the feeling of 'movement' to what would otherwise be a somewhat static, or unchanching, element. ");
        
        concreteLabels.add("Automating the Q");
        concreteTexts.add("Q automation is often used in conjunction with cut-off automation to add further timbral variation over time. Automating the q alters the degree of emphasis on a peak at the filter's cut-off point in the case of high and low-pass filters, and changes the band-width in notch, bandpass and peak filters.");
        
        concreteLabels.add("Automating the Peak Gain");
        concreteTexts.add("Dunno");
        
    }
    
    void addTextToOblique()
    {
        obliqueTexts.add("Simulate infinity");
        obliqueTexts.add("Negative Space as foreground");
        obliqueTexts.add("Remove specifics and convert to ambiguities");
        obliqueTexts.add("Humanize something free of error");
        obliqueTexts.add("Randomize something free of error");
        obliqueTexts.add("Go to an extreme before moving back to a more comfortable space");
        obliqueTexts.add("Make the distance reveal the details.");
        obliqueTexts.add("Flatten your perception");
        obliqueTexts.add("Emphasize differences");
        obliqueTexts.add("Remove ambiguities and convert to specifics");
        obliqueTexts.add("Make repetition a form of change");
        obliqueTexts.add("Find difficulty in what should be a simple task");
        obliqueTexts.add("All of it but less");
        obliqueTexts.add("Do the bare minimum");
        obliqueTexts.add("Make audible your mistakes");
        obliqueTexts.add("Make your room");
        obliqueTexts.add("Remove the most important thing");
    }
    void buttonStateChanged(Button*) override;
    void buttonClicked(Button*) override;
    
    int currentItemIndex = 1;
    juce::Array<String> obliqueTexts;
    juce::Array<String> concreteTexts;
    juce::Array<String> concreteLabels;
    
    juce::Random rand;
    int maxNum;
    
    juce::Font textFont {"Arial", 17, Font::plain};
    juce::Font labelFont {"Arial", 14, Font::plain};
    
    static String concreteToolTip;
    static String obliqueToolTip;
    static String lessonsToolTip;
    static String nextToolTip;
    static String previousToolTip;
    static String frequencyToolTip;
    static String qToolTip;
    static String gainToolTip;
    static String volumeToolTip;
    static String filterChoiceToolTip;
    static String biquadChoiceToolTip;
    static String textToolTip;
    TooltipWindow tooltipWindow {this, 1000};
    
    Slider freqSlider {Slider::RotaryHorizontalVerticalDrag,
    Slider::TextBoxBelow};
    Slider qSlider {Slider::RotaryHorizontalVerticalDrag,
    Slider::TextBoxBelow};
    Slider peakGainSlider {Slider::RotaryHorizontalVerticalDrag,
    Slider::TextBoxBelow};
    Slider volumeSlider {Slider::RotaryHorizontalVerticalDrag,
    Slider::TextBoxBelow};
    ComboBox filterChoice;
    ComboBox biquadChoice;
    
    
    juce::ComboBox obliqueConcreteChoices;
    juce::TextButton oblique;
    juce::TextButton concrete;
    juce::Label text;
    ArrowButton next {"next", 0.0, juce::Colours::white};
    ArrowButton previous {"previous", 0.5, juce::Colours::white};
    juce::Label mixLabel;
    juce::Label decayLabel;
    juce::Label lpfLabel;
    
    OtherLookAndFeelSlider otherLookAndFeelSlider;

    std::ofstream bufferFile;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewObliqueFilterAudioProcessor& processor;

public:
    
    AudioProcessorValueTreeState::ButtonAttachment
    mObliqueAttachment { processor.getValueTreeState(), "oblique", oblique };
    AudioProcessorValueTreeState::ButtonAttachment mConcreteAttachment
    { processor.getValueTreeState(), "concrete", concrete };
    AudioProcessorValueTreeState::ComboBoxAttachment mObConcreteAttachment { processor.getValueTreeState(), "obliqueConcrete", obliqueConcreteChoices};
    AudioProcessorValueTreeState::SliderAttachment mFrequencyAttachment {processor.getValueTreeState(), FREQ_ID, freqSlider };
    AudioProcessorValueTreeState::SliderAttachment mResonanceAttachment {processor.getValueTreeState(), Q_ID, qSlider };
    AudioProcessorValueTreeState::SliderAttachment mGainAttachment {processor.getValueTreeState(), PEAKGAIN_ID, peakGainSlider };
    AudioProcessorValueTreeState::SliderAttachment mVolumeAttachment
    {processor.getValueTreeState(), VOLUME_ID, volumeSlider};
    AudioProcessorValueTreeState::ComboBoxAttachment mfilterChoiceAttachment {processor.getValueTreeState(), CHOICE_ID, filterChoice};
    AudioProcessorValueTreeState::ComboBoxAttachment mbiquadChoiceAttachment {processor.getValueTreeState(), BIQCHOICE_ID, biquadChoice};


    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewObliqueFilterAudioProcessorEditor)
};
