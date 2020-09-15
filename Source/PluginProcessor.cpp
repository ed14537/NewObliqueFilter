/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


String NewObliqueFilterAudioProcessor::paramOblique ("Oblique");
String NewObliqueFilterAudioProcessor::paramConcrete ("Concrete");
String NewObliqueFilterAudioProcessor::paramObliqueConcrete
 ("ObliqueConcrete");
String NewObliqueFilterAudioProcessor::paramFrequency(FREQ_ID);
String NewObliqueFilterAudioProcessor::paramQ(Q_ID);
String NewObliqueFilterAudioProcessor::paramVolume(VOLUME_ID);
String NewObliqueFilterAudioProcessor::paramPeakGain(PEAKGAIN_ID);

//==============================================================================
NewObliqueFilterAudioProcessor::NewObliqueFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    parameters (*this, nullptr, "Filter", createParameterLayout())
#endif
{
    //parameters.state = ValueTree("savedparams");
}

NewObliqueFilterAudioProcessor::~NewObliqueFilterAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout NewObliqueFilterAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> params;

    auto freqParam = std::make_unique<AudioParameterFloat>(FREQ_ID, FREQ_NAME, NormalisableRange<float>(20.0f, 20000.0f, 25.0f, 0.5f, false), 200.0f);
    auto qParam = std::make_unique<AudioParameterFloat>(Q_ID, Q_NAME, NormalisableRange<float> (0.001f, 1.0f, 0.001f), 0.1f);
    auto volumeParam = std::make_unique<AudioParameterFloat>(VOLUME_ID, VOLUME_NAME, NormalisableRange<float>(-48.0f, 15.0f, 0.1f), 0.0f);
    auto peakGainParam = std::make_unique<AudioParameterFloat>(PEAKGAIN_ID, PEAKGAIN_NAME, NormalisableRange<float>(-48.0f, 30.0f, 0.1f), 0.0f);
    auto filterChoiceParam = std::make_unique<AudioParameterFloat>(CHOICE_ID, CHOICE_NAME, NormalisableRange<float>(1, 2, 1), 1);
    auto biquadChoiceParam = std::make_unique<AudioParameterFloat>(BIQCHOICE_ID, BIQCHOICE_NAME, NormalisableRange<float>(1, 7, 1), 1);
    auto obliqueParam = std::make_unique<AudioParameterFloat>
        (paramOblique, TRANS("Oblique"),
        NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto concreteParam = std::make_unique<AudioParameterFloat>
        (paramConcrete, TRANS("Concrete"),
        NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto obliqueConcreteParam =  std::make_unique<AudioParameterFloat>
        (paramObliqueConcrete, TRANS("Oblique Concrete"),
        NormalisableRange<float>(0.0f, 20.0f), 1.0f);
    

    params.push_back(std::move(freqParam));
    params.push_back(std::move(qParam));
    params.push_back(std::move(volumeParam));
    params.push_back(std::move(peakGainParam));
    params.push_back(std::move(filterChoiceParam));
    params.push_back(std::move(biquadChoiceParam));
    params.push_back(std::move(obliqueParam));
    params.push_back(std::move(concreteParam));
    params.push_back(std::move(obliqueConcreteParam));

    return { params.begin(), params.end() };
}



//==============================================================================
const String NewObliqueFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewObliqueFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewObliqueFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewObliqueFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewObliqueFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewObliqueFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewObliqueFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewObliqueFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String NewObliqueFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewObliqueFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewObliqueFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int channel = 0; channel < kChannels; channel++)
    {
        filter[channel].prepareToPlay(sampleRate, samplesPerBlock);
    }
    
}

void NewObliqueFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewObliqueFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void NewObliqueFilterAudioProcessor::parameterChanged(const String &parameterID, float newValue)
{
    if(parameterID == paramFrequency)
    {
        sliderFreqValue = ((*parameters.getRawParameterValue(FREQ_ID) / 20000) * 0.49);
        sliderFrequencyValue = *parameters.getRawParameterValue(FREQ_ID);
    } else if (parameterID == paramQ)
    {
        sliderQValue = *parameters.getRawParameterValue(Q_ID);
    } else if (parameterID == paramVolume)
    {
        sliderVolumeValue = *parameters.getRawParameterValue(VOLUME_ID);
    } else if (parameterID == paramPeakGain)
    {
        sliderPeakGainValue = *parameters.getRawParameterValue(PEAKGAIN_ID);
    }
}

void NewObliqueFilterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //auto sliderFreqValue = parameters.getRawParameterValue(FREQ_ID);
    //auto sliderqValue = parameters.getRawParameterValue(Q_ID);
    //auto sliderVolumeValue = parameters.getRawParameterValue(VOLUME_ID);
    //float sliderFreqValue = ((*parameters.getRawParameterValue(FREQ_ID) / 20000) * 0.49);
    float sliderFrequencyValue = *parameters.getRawParameterValue(FREQ_ID);
    float sliderQValue = *parameters.getRawParameterValue(Q_ID);
    float sliderVolumeValue = *parameters.getRawParameterValue(VOLUME_ID);
    float sliderPeakGainValue = *parameters.getRawParameterValue(PEAKGAIN_ID);

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        //input data
        const float* inputData = buffer.getReadPointer(channel);

        float* outputData = buffer.getWritePointer(channel);
        
        //place audio samples into buffer
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            //get current value from read pointer
            float inputSample = inputData[sample];

            switch ((int)filterChoice) {
            case BiquadFilter:
                filter[channel].setBiquad((int)biquadChoice, sliderFrequencyValue, sliderQValue, sliderPeakGainValue);
                outputData[sample] = filter[channel].processBiquad(inputSample);
                //filter[channel].setButterworth(sliderFrequencyValue);
                //outputData[channel] = filter[channel].processButterworth(inputSample);
                break;
            case Bilinear:
                filter[channel].setButterworth((int)biquadChoice, sliderFrequencyValue, sliderQValue, sliderPeakGainValue);
                outputData[sample] = filter[channel].processButterworth(inputSample);
            }
            outputData[sample] = outputData[sample] * Decibels::decibelsToGain(sliderVolumeValue);
        }
    }
}

AudioProcessorValueTreeState& NewObliqueFilterAudioProcessor::getValueTreeState()
{
    return parameters;
}

//==============================================================================
bool NewObliqueFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewObliqueFilterAudioProcessor::createEditor()
{
    return new NewObliqueFilterAudioProcessorEditor (*this);
}

//==============================================================================
void NewObliqueFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    MemoryOutputStream stream(destData, false);
    parameters.state.writeToStream (stream);
}

void NewObliqueFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData (data, sizeInBytes);
    if (tree.isValid()) {
        parameters.state = tree;
    } 
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewObliqueFilterAudioProcessor();
}
