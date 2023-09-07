//
//  OscSender.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 06.06.23.
//

#include "OscSender.h"

OscSender::OscSender() {
    if (! connect ("130.149.23.24", 4455))
        showConnectionErrorMessage ("Error: could not connect to UDP port 9001.");
}

void OscSender::sendMessage(Source& source, Parameter parameter) {
    if (source.sourceIdx > 0) {
        if (parameter == PARAM_SOURCE_IDX) {
            juce::OSCMessage oscMessagePosition("/source/pos/xyz", source.sourceIdx, source.xPosition, source.yPosition, source.zPosition);
            juce::OSCMessage oscMessageGain1("/send/gain",source.sourceIdx, 0, source.gain1);
            juce::OSCMessage oscMessageGain2("/send/gain",source.sourceIdx, 1, source.gain2);
            if (! send(oscMessagePosition) || !send(oscMessageGain1) || !send(oscMessageGain2))
                showConnectionErrorMessage("Error: could not send OSC message.");
            return;
        }
        else {
            juce::OSCMessage oscMessage("/");
            if (parameter == PARAM_POS) {
                oscMessage = juce::OSCMessage("/source/pos/xyz", source.sourceIdx, source.xPosition, source.yPosition, source.zPosition);
            } else if (parameter == PARAM_GAIN_1) {
                oscMessage = juce::OSCMessage("/send/gain",source.sourceIdx, 0, source.gain1);
            } else if (parameter == PARAM_GAIN_2) {
                oscMessage = juce::OSCMessage("/send/gain",source.sourceIdx, 1, source.gain2);
            }
            if (! send(oscMessage))
                showConnectionErrorMessage("Error: could not send OSC message.");
        }
    }
}

void OscSender::showConnectionErrorMessage (const juce::String& messageText) {
      juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                              "Connection error",
                                              messageText,
                                              "OK");
}
