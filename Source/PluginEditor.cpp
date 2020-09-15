/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
String NewObliqueFilterAudioProcessorEditor::concreteToolTip ("The concrete mode provides you with a series of lessons aimed to teach you the basics of reverb usage in a variety of production and mix settings.");

String NewObliqueFilterAudioProcessorEditor::obliqueToolTip ("The oblique mode provides you with a series of prompts that are aimed to stimulate creativity in the sound design and mixing process. These will not provide direct instructions; only abstract concepts to use as brain food.");

String NewObliqueFilterAudioProcessorEditor::lessonsToolTip ("This selection box allows you to choose which lesson you'd like to undertake. Note that this will only appear for the Concrete Mode. To change the Oblique prompt, use the next and previous arrows at the bottom right of the User Interface");

String NewObliqueFilterAudioProcessorEditor::nextToolTip ("Loads the next prompt.");

String NewObliqueFilterAudioProcessorEditor::previousToolTip ("Re-loads the previous prompt");

String NewObliqueFilterAudioProcessorEditor::frequencyToolTip ("Adjusts the cut-off frequency of the selected filter. On a low-pass, for example, increasing this value increases the point on the frequency spectrum at which high-frequency input signals are attenuated.");

String NewObliqueFilterAudioProcessorEditor::qToolTip("Sets the Q factor of the filter, or in other words, represents the narrowness (in Hz) of the peak at a given cut-off frequency.");

String NewObliqueFilterAudioProcessorEditor::volumeToolTip("Sets the volume of the output of the filter.");

String NewObliqueFilterAudioProcessorEditor::gainToolTip("Represents the resonance of the filter or height of the peak at a given cut-off frequency.");

String NewObliqueFilterAudioProcessorEditor::filterChoiceToolTip("This menu allows you to select the type of filter you would like to use. Please note that this selection changes the behaviour of the other knob. For example, setting the filter choice to low-pass will make increases in the cut-off filter out more of the sound, whilst the inverse is true for a high pass.");

String NewObliqueFilterAudioProcessorEditor::biquadChoiceToolTip("This menu allows you to set the biquad Filter type. This is another type of filter that has certain advantages and disadvantages, but generally speaking it has the same effect as the regular filter choice.");

NewObliqueFilterAudioProcessorEditor::NewObliqueFilterAudioProcessorEditor (NewObliqueFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&otherLookAndFeelSlider);
    addAndMakeVisible(&freqSlider);
    freqSlider.setTooltip(frequencyToolTip);
    freqSlider.setSkewFactorFromMidPoint(4000);


    addAndMakeVisible(&qSlider);
    qSlider.setTooltip(qToolTip);

    addAndMakeVisible(&volumeSlider);
    volumeSlider.setTooltip(volumeToolTip);

    addAndMakeVisible(&peakGainSlider);
    peakGainSlider.setTooltip(gainToolTip);

    filterChoice.setName("filter choice");
    filterChoice.addItem("Biquad", 1);
    //filterChoice.addItem("Bilinear", 4);
    filterChoice.setSelectedId(1);
    filterChoice.addListener(this);
    addAndMakeVisible(&filterChoice);
    filterChoice.setTooltip(filterChoiceToolTip);

    biquadChoice.setName("biquad");
    biquadChoice.addItem("Low Pass", 1);
    biquadChoice.addItem("High Pass", 2);
    biquadChoice.addItem("Band Pass", 3);
    biquadChoice.addItem("Notch", 4);
    biquadChoice.addItem("Peak", 5);
    biquadChoice.addItem("Low Shelf", 6);
    biquadChoice.addItem("High Shelf", 7);
    biquadChoice.setSelectedId(static_cast<int>
                               (*processor.getValueTreeState()
                                .getRawParameterValue(BIQCHOICE_ID)));
    biquadChoice.addListener(this);
    addAndMakeVisible(&biquadChoice);
    biquadChoice.setTooltip(biquadChoiceToolTip);
    
    addAndMakeVisible(oblique);
    oblique.setName("Oblique");
    oblique.setComponentID("oblique");
    oblique.setButtonText("Oblique");
    oblique.setRadioGroupId(1);
    oblique.addListener(this);
    oblique.setTooltip(obliqueToolTip);
    
    addAndMakeVisible(concrete);
    concrete.setName("Concrete");
    concrete.setComponentID("concrete");
    concrete.setButtonText("Concrete");
    concrete.setRadioGroupId(1);
    concrete.addListener(this);
    concrete.setTooltip(concreteToolTip);
    
    addAndMakeVisible(obliqueConcreteChoices);
    obliqueConcreteChoices.setName("Oblique Concrete");
    obliqueConcreteChoices.setComponentID("obConcrete");
    obliqueConcreteChoices.setTextWhenNothingSelected("Lessons");
    obliqueConcreteChoices.setTooltip(lessonsToolTip);
    obliqueConcreteChoices.setSelectedItemIndex(currentItemIndex);
    obliqueConcreteChoices.addListener(this);
    
    next.setComponentID("next");
    next.addListener(this);
    next.setTooltip(nextToolTip);
    addAndMakeVisible(next);
    
    previous.setComponentID("previous");
    previous.addListener(this);
    previous.setTooltip(previousToolTip);
    addAndMakeVisible(previous);
    
    concrete.triggerClick();
    
    addAndMakeVisible(text);
    addAndMakeVisible(tooltipWindow);
    
    addTextToOblique();
    addTextToConcrete();
    int i = 1;
    
    for(String s : concreteLabels) {
        obliqueConcreteChoices.addItem(s, i);
        i++;
    }
    
    text.setName("lessons");
    text.setText(obliqueTexts.getReference(currentItemIndex), dontSendNotification);
    obliqueConcreteChoices.setSelectedId(currentItemIndex);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500,600);
}

NewObliqueFilterAudioProcessorEditor::~NewObliqueFilterAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void NewObliqueFilterAudioProcessorEditor::comboBoxChanged(ComboBox* box)
{
    if(box == &filterChoice)
    {
        if(box->getSelectedId() == 1)
        {
            biquadChoice.setVisible(true);
            biquadChoice.setAlpha(1.0);
        } else
        {
            biquadChoice.setVisible(false);
            biquadChoice.setAlpha(0.0);
        }
        processor.filterChoice = filterChoice.getSelectedIdAsValue().getValue();
        processor.biquadChoice = biquadChoice.getSelectedIdAsValue().getValue();
    } else if (biquadChoice.isVisible() && box == &biquadChoice)
    {
        processor.filterChoice = filterChoice.getSelectedIdAsValue().getValue();
        processor.biquadChoice = biquadChoice.getSelectedIdAsValue().getValue();
    } else if (box == &obliqueConcreteChoices)
    {
        text.setText(concreteTexts.getReference
                     (box->getSelectedId()-1),
        dontSendNotification);
    }
}

void NewObliqueFilterAudioProcessorEditor::buttonStateChanged(Button* b)
{
    
    
}

void NewObliqueFilterAudioProcessorEditor::buttonClicked(Button* b)
{
    if(b == &next)
    {
        currentItemIndex++;
        if(concrete.getToggleState())
        {
            if(currentItemIndex >= obliqueConcreteChoices
            .getNumItems())
            {
                currentItemIndex = 1;
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);

            } else
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);
            }
        } else
        {
            
            text.setText(obliqueTexts.getReference
                         (rand.nextInt(obliqueTexts.size()-1)),
                         dontSendNotification);
        }
    } else if(b == &previous) {
        currentItemIndex--;
        if(concrete.getToggleState())
        {
            if(currentItemIndex >= 0)
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);
            } else
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(obliqueConcreteChoices
                                        .getNumItems()-1);
                currentItemIndex = obliqueConcreteChoices
                .getNumItems()-1;
            }
        } else {
            if(currentItemIndex >= 0)
            {
                text.setText(obliqueTexts
                             .getReference(currentItemIndex),
                             dontSendNotification);
            } else
            {
                currentItemIndex = obliqueTexts.size() - 1;
                       
                text.setText(obliqueTexts
                             .getReference(currentItemIndex),
                             dontSendNotification);
            }
        }
    } else if (b == &oblique)
    {
        obliqueConcreteChoices.setEnabled(false);
        obliqueConcreteChoices.setVisible(false);
        text.setText(obliqueTexts.getReference(0),
                     dontSendNotification);
        oblique.setToggleState(true, dontSendNotification);
        concrete.setToggleState(false, dontSendNotification);
        concrete.setAlpha(0.5);
        oblique.setAlpha(1.0);
    } else if (b == &concrete)
    {
        obliqueConcreteChoices.setEnabled(true);
        obliqueConcreteChoices.setVisible(true);
        oblique.setToggleState(false, dontSendNotification);
        concrete.setToggleState(true, dontSendNotification);
        text.setText(concreteTexts
                     .getReference(obliqueConcreteChoices
                                   .getSelectedId()-1),
                     dontSendNotification);
        oblique.setAlpha(0.5);
        concrete.setAlpha(1.0);
    }
    
}

//==============================================================================
void NewObliqueFilterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
// (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::grey);

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.setFont(textFont);
    //auto topBox = getLocalBounds();
    Rectangle<int> topBox (0,(getHeight()-20)/8-10, getWidth()-20, 50);
    Rectangle<int> box (0, getHeight()/2-300, getWidth()-20, getHeight()-20/2);
    //auto box = getLocalBounds();
    //topBox.setBounds(0, 0, getWidth()-20, getHeight()-10/2);
    //box.setBounds(0, getHeight()/2, getWidth()-20, getHeight()-10/2);
    box = box.withTop(20);
    
    text.setColour(Label::textColourId, juce::Colours::white);
    text.setFont(labelFont);
    
    const auto width = topBox.getWidth();
    const auto bottomWidth = box.getWidth()/4;
    g.drawFittedText(TRANS("Frequency"), box.removeFromLeft(bottomWidth), Justification::centred, 1);
    g.drawFittedText(TRANS("Q"), box.removeFromLeft(bottomWidth), Justification::centred, 1);
    g.drawFittedText(TRANS("Volume"), box.removeFromLeft(bottomWidth), Justification::centred, 1);
    g.drawFittedText(TRANS("Peak Gain"), box.removeFromLeft(bottomWidth), Justification::centred, 1);
    //g.drawFittedText(TRANS("Filter Type"), topBox.removeFromLeft(width), Justification::centred, 1);
    g.drawFittedText(TRANS("Filter Type"), topBox.removeFromLeft(width), Justification::centred, 1);
    
    /*g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawText("Frequency", (getWidth() / 2) - 200, (((getHeight() / 4) * 1) - 30), 200, 50, Justification::centred, false);
    g.drawText("Q", (getWidth() / 2) - 200, (((getHeight() / 4) * 2) - 80), 200, 50, Justification::centred, false);
    g.drawText("Volume", (getWidth() / 2) - 200, (((getHeight() / 4) * 3) - 130), 200, 50, Justification::centred, false);
    g.drawText("Peak Gain", (getWidth() / 2) - 200, (((getHeight() / 4) * 4) - 180), 200, 50, Justification::centred, false);
    g.drawText("Filter Type:", 120, 5, 80, 50, Justification::centred, false);
    g.drawText("Biquad Type:", 110, 40, 80, 50, Justification::centred, false);*/
}

void NewObliqueFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //auto topBox = getLocalBounds();
    //auto box = getLocalBounds();
    Rectangle<int> topBox (0,0, getWidth()-20, (getHeight()-20)/8);
    Rectangle<int> box (0, topBox.getHeight() + 30, getWidth()-20, getHeight()-10);
    Rectangle<int> lowMidBox(0, getHeight()/3, getWidth()-20, getHeight()-10/6);
    Rectangle<int> bottomBox(0, getHeight()/3 - 250, getWidth()-20, getHeight()-10/3);
    //topBox.setBounds(0, 0, getWidth()-20, getHeight()-10/2);
    //box.setBounds(0, getHeight()/2, getWidth()-20, getHeight()-10/2);
    box = box.withBottom(300);
    
    const auto width = topBox.getWidth();
    const auto bottomWidth = box.getWidth()/4;
    
    //filterChoice.setBounds(topBox.removeFromLeft(width));
    biquadChoice.setBounds(topBox.removeFromLeft(width));
    freqSlider.setBounds(box.removeFromLeft(bottomWidth).reduced(10));
    qSlider.setBounds(box.removeFromLeft(bottomWidth).reduced(10));
    volumeSlider.setBounds (box.removeFromLeft(bottomWidth)
                            .reduced(10));
    peakGainSlider.setBounds(box.removeFromLeft(bottomWidth)
                            .reduced(10));
    
    const auto midWidth = lowMidBox.getWidth() / 3;
       obliqueConcreteChoices.setBounds(10, getHeight()/2+30,
                                        midWidth+50, 30);
       oblique.setBounds(midWidth*2 + 25,  getHeight()/2+30, 75, 30);
       concrete.setBounds(midWidth*2 + 100, getHeight()/2+30, 75, 30);
    
    /*filterChoice.setBounds(200, 15, 250, 30);
    biquadChoice.setBounds(200, 50, 250, 30);
    freqSlider.setBounds((getWidth() / 2) - 60, (((getHeight() / 4) * 1) - 20), 200, 50);
    qSlider.setBounds((getWidth() / 2) - 60, (((getHeight() / 4) * 2) - 70), 200, 50);
    volumeSlider.setBounds((getWidth() / 2) - 60, (((getHeight() / 4) * 3)- 120), 200, 50);
    peakGainSlider.setBounds((getWidth() / 2) - 60, (((getHeight() / 4) * 4) - 170), 200, 50);*/
    
    previous.setBounds(getWidth()-100, getHeight()-40, 50, 30);
    next.setBounds(getWidth()-50, getHeight()-40, 50, 30);
    text.setBounds(bottomBox.reduced(10).removeFromBottom(250));
    text.toBack();
    next.setAlpha(0.5);
    text.setFont(textFont);
    previous.setAlpha(0.5);
}
