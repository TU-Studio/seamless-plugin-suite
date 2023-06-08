//
//  MainServer.h
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#ifndef MainServer_h
#define MainServer_h

#include <JuceHeader.h>
#include "PluginConnection.h"

class MainServer : public juce::InterprocessConnectionServer, private PluginConnection::Listener
{
public:
    MainServer();
    ~MainServer() override;
    
    class Listener {
    public:
        virtual void newPluginConnection(PluginConnection* pluginConnection) = 0; // pure virtual function
        virtual void deletedPluginConnection(PluginConnection* pluginConnection) = 0; // pure virtual function
        virtual void parameterChanged(PluginConnection* pluginConnection, Parameter parameter, float value1, float value2, float value3) = 0; // pure virtual funtion
    };
    void addListener(Listener *);
    void removeListener(Listener *);
    
private:
    PluginConnection* createConnectionObject() override;
    std::vector<PluginConnection*> mainConnections;
    juce::ListenerList<Listener> listenerList;
    
    void forwardMessage(PluginConnection* pluginConnection, const juce::MemoryBlock& memoryBlock) override;
    void disconnected(PluginConnection* pluginConnection) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainServer)
};

#endif /* MainServer_h */
