//
//  MainServer.cpp
//  SeamlessPluginSuite
//
//  Created by Fares Schulz on 03.05.23.
//

#include "MainServer.h"

MainServer::MainServer() : InterprocessConnectionServer() {}

MainServer::~MainServer() {
    stop();
    for (unsigned long i = 0; i < mainConnections.size(); i++) {
        mainConnections[i]->removeListener(this);
        delete mainConnections[i];
    }
    mainConnections.clear();
    listenerList.call([] (Listener& l) {l.deletedMainServer();});
}

void MainServer::addListener(Listener* listener) {
    listenerList.add(listener);
}

void MainServer::removeListener(Listener* listener) {
    listenerList.remove(listener);
}

PluginConnection* MainServer::createConnectionObject() {
    PluginConnection* newPluginConnection = new PluginConnection;
    mainConnections.push_back(newPluginConnection);
    newPluginConnection->addListener(this);
    std::cout << "Main plugin received new connection! N = " << mainConnections.size() << std::endl;
    
    listenerList.call([newPluginConnection] (Listener& l) {l.newPluginConnection(newPluginConnection);});
     
    return newPluginConnection;
}

void MainServer::forwardMessage(PluginConnection* pluginConnection, const juce::MemoryBlock& memoryBlock) {
    std::cout << "Message:" << std::endl;
    Message* message = (Message*) memoryBlock.getData();
    std::cout << "Parameter: " << message->parameter << std::endl;
    std::cout << "Value 1: " << message->value1 << std::endl;
    std::cout << "Value 2: " << message->value2 << std::endl;
    std::cout << "Value 3: " << message->value3 << std::endl;
    Parameter parameter = message->parameter;
    float value1 = message->value1;
    float value2 = message->value2;
    float value3 = message->value3;
    listenerList.call([pluginConnection, parameter, value1, value2, value3] (Listener& l) {l.parameterChanged(pluginConnection, parameter, value1, value2, value3);});
}

void MainServer::disconnected(PluginConnection *pluginConnection) {
    listenerList.call([pluginConnection] (Listener& l) {l.deletedPluginConnection(pluginConnection);});
    
    for (unsigned long i = 0; i < mainConnections.size(); i++) {
        if (mainConnections[i] == pluginConnection) {
            mainConnections[i]->removeListener(this);
            mainConnections.erase(mainConnections.begin()+(long) i);
            delete pluginConnection;
        }
    }
    std::cout << "Main plugin deleted connection! N = " << mainConnections.size() << std::endl;
}
