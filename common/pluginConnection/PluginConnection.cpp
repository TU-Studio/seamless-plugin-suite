//
//  PluginConnection.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#include "PluginConnection.h"

PluginConnection::PluginConnection() : InterprocessConnection(true, 15) {
}

PluginConnection::~PluginConnection() {
    disconnect(10);
}

void PluginConnection::addListener(Listener* listener) {
    listenerList.add(listener);
}

void PluginConnection::removeListener(Listener* listener) {
    listenerList.remove(listener);
}

void PluginConnection::connect() {
    connectToSocket("localhost", IPC_PORT, 5000);
}

void PluginConnection::updateState(juce::AudioProcessorValueTreeState& apvts, juce::StringArray parameterList, juce::StringArray settingsList) {
    if (isConnected()) {
        // no need to initialize the parameterList since setStateInformation calls parameterChanged for each parameter
        // but when the main server is started after the plugin, the plugin needs to initialize the parameterList
        for (auto & parameter : parameterList) {
            parameterChanged(parameter, apvts.getRawParameterValue(parameter)->load());
        }
        for (auto & setting : settingsList) {
            parameterChanged(setting, apvts.state.getChild(0).getProperty(setting));
        }
    }
}

void PluginConnection::parameterChanged(const juce::String &parameterID, float newValue)
{
    std::cout << "Parameter changed: " << parameterID << " with value: " << newValue << std::endl;
    if (isConnected())
    {
        if (parameterID == OSCParameters::SOURCE_IDX_ID) {
            Message message;
            message.parameter = Parameter::PARAM_SOURCE_IDX;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == OSCParameters::GAIN_1_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_1;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID ==  OSCParameters::GAIN_2_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_2;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == OSCParameters::GAIN_3_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_3;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == OSCParameters::GAIN_4_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_GAIN_4;
            message.value1 = (float) newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == OSCParameters::POS_X_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_POS;
            message.value1 = newValue;
            message.value2 = 99.f;
            message.value3 = 99.f;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == OSCParameters::POS_Y_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_POS;
            message.value1 = 99.f;
            message.value2 = newValue;
            message.value3 = 99.f;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        } else if (parameterID == OSCParameters::POS_Z_ID.getParamID()) {
            Message message;
            message.parameter = Parameter::PARAM_POS;
            message.value1 = 99.f;
            message.value2 = 99.f;
            message.value3 = newValue;
            juce::MemoryBlock memoryBlock (&message, sizeof(Message));
            sendMessage(memoryBlock);
        }
    }
}
    
void PluginConnection::connectionMade() {
    listenerList.call([this] (Listener& l) {l.connected(this);});
    std::cout << "Connection estblished!" << std::endl;
}

void PluginConnection::connectionLost() {
    listenerList.call([this] (Listener& l) {l.disconnected(this);});
    std::cout << "Conection lost!" << std::endl;
}

void PluginConnection::messageReceived(const juce::MemoryBlock& memoryBlock) {
    listenerList.call([this, memoryBlock](Listener& l) {l.forwardMessage(this, memoryBlock);});
}
