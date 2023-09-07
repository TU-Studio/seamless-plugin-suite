//
//  SendParameters.hpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#ifndef SendParameters_h
#define SendParameters_h

#include <JuceHeader.h>

class SendParameters {
public:
    
    SendParameters();
    ~SendParameters();
    
    inline static const juce::ParameterID
        
        GAIN_1_ID = {"param_gain_1", 1},
        GAIN_2_ID = {"param_gain_2", 1},
        POS_X_ID = {"param_pos_x", 1},
        POS_Y_ID = {"param_pos_y", 1};
    
    inline static const juce::String
        
        GAIN_1_NAME = "Send HOA",
        GAIN_2_NAME = "Send WFS",
        POS_X_NAME = "X Position",
        POS_Y_NAME = "Y Position",
    
        // not automatable SendParameters
        SOURCE_IDX_NAME = "Source Index";
    
    static juce::StringArray getPluginParameterList();
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    static void createNotAutomatableValueTree();
    static void clearNotAutomatableValueTree();
    static juce::StringArray getSettingsList();
    static juce::ValueTree getNotAutomatableValueTree();
    
private:
    
    inline static juce::StringArray parameterList;
    inline static juce::StringArray settingsList;
    inline static juce::ValueTree notAutomatableParameterValueTree;
    
    inline static juce::NormalisableRange<float> GAIN_RANGE {0.f, 1.f, 0.01f};
    inline static juce::NormalisableRange<float> POS_RANGE {-10.f, 10.f, 0.01f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SendParameters)
};

#endif /* SendParameters_h */
