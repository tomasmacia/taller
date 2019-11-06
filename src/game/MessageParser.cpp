//
// Created by axel on 1/11/19.
//

#include <vector>
#include <string>
#include <cstring>

#include "MessageId.h"
#include "MessageParser.h"

using namespace std;

//API
//=========================================================================================
void MessageParser::parse(string rawMessage, char separatorCharacter) {
    clear();
    lastParsedMessage = split(rawMessage,separatorCharacter);
}

void MessageParser::parseModel(string rawMessage, char separatorCharacter, char separatorGameObjectCharacter) {
    for (auto vector : *lastParsedMessages) {
        vector.clear();
    }
    delete(lastParsedMessages);
    lastParsedMessages = nullptr;
    lastParsedMessages = new vector<vector<string>>();

    string messageWithoutPadding = split(rawMessage, '*')->at(0); // TODO REMOVE PADDING;

    vector<string> gameObjects = *split(messageWithoutPadding, separatorGameObjectCharacter);

    for (auto &gameObject : gameObjects) {
        lastParsedMessages->push_back(*split(gameObject, separatorCharacter));
    }
}

MessageId MessageParser::getHeader() {

    if (lastParsedMessage != nullptr && !lastParsedMessage->empty()){
        return (MessageId)stoi(lastParsedMessage->at(0));
    }
    else {
        return UNDEFINED;
    }
}

vector<string> MessageParser::extractMeaningfulMessagesFromStream(char *buffer, char endSerializationChar) {
    vector<string> messages;

    char OBJECT_SEPARATOR = '|'; // TODO REMOVE HARDCODING;
    int i = 0;
    string extractedMessage;
    while (buffer[i] != endSerializationChar) {
        if (buffer[i] == OBJECT_SEPARATOR) {
            messages.push_back(extractedMessage);
            extractedMessage.clear();
        } else {
            extractedMessage += buffer[i];
        }

        i++;
    }

    return messages;
}

string MessageParser::extractMeaningfulMessageFromStream(char *buffer, char endSerializationChar){

    string extractedMessage = "";
    int i = 0;
    while (buffer[i] != endSerializationChar){
        extractedMessage += buffer[i];
        i++;
    }
    extractedMessage += buffer[i];

    return extractedMessage;
}

void MessageParser::clear(){
    lastParsedMessage->clear();
}

//SPLIT
//=========================================================================================
vector<string>* MessageParser::split(const string& s, const char& c)
{
    string buff{""};
    vector<string>* v = new vector<string>();

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v->push_back(buff); buff = ""; }
    }
    if(buff != "") v->push_back(buff);

    return v;
}

//CONSTRUCTOR
//=========================================================================================
MessageParser::MessageParser() {
    lastParsedMessage = new vector<string>;
}

//DESTROY
//=========================================================================================
MessageParser::~MessageParser() {
    clear();
    delete lastParsedMessage;
    lastParsedMessage = nullptr;
}

































/*
string MessageParser::extractMeaningfulMessageFromStream(char* buffer, char separator, char endSerializationChar){
    //cleans buffer up

    std::string stringSeparator;
    stringSeparator = separator;

    std::string stringEndSerializationChar;
    stringEndSerializationChar = endSerializationChar;

    std::string stringedBuffer = buffer;
    std::string delimiter = stringSeparator + stringEndSerializationChar;
    std::string message = stringedBuffer.substr(0, stringedBuffer.find(delimiter));

    //le quito al buffer lo que acabo de parsear
    int messageLength = message.length();

    std::string restOfBuffer = stringedBuffer.substr(stringedBuffer.find(delimiter),
                                                     stringedBuffer.length() - messageLength);

    //(TODO) QUIZAS SEA COSTOSO A LA LARGA EN RECURSOS PORQUE SE HACE TODO EL TIEMPO ESTO
    char* cleanedBuf;
    strcpy(cleanedBuf, restOfBuffer.c_str());
    buffer = cleanedBuf;

    return message;
}*/
