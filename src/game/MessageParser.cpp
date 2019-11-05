//
// Created by axel on 1/11/19.
//

#include <vector>
#include <string>
#include <cstring>
#include <list>
#include <iostream>

#include "MessageId.h"
#include "MessageParser.h"

using namespace std;

//API
//=========================================================================================
vector<string> MessageParser::extractMeaningfulMessagesFromStream(char *buffer, ObjectSerializer objectSerializer){

    vector<string> partialMessages = getPartialMessagesFrom(buffer,objectSerializer);
    vector<string> completeMessages;

    for (auto a: partialMessages){
        //cout<<"parseado: "<<a<<endl;
    }

    if (partialMessages.size() == 0){
        return partialMessages;
    }

    if (partialMessages.size() == 1){
        string message =  partialMessages.at(0);

        if (isACompleteMessage(message,objectSerializer)){
            completeMessages.push_back(message);
        }
        else{
            if(isACompleteMessage(lastPreviousIncompleteMessage + message,objectSerializer)){
                //cout << "pruebo con: " << (lastPreviousIncompleteMessage + message) << endl;
                completeMessages.push_back((lastPreviousIncompleteMessage + message));
            }
            else{
                lastPreviousIncompleteMessage = message;
            }
        }
    }

    else{

        string firstMessage = partialMessages.at(0);

        if (!isACompleteMessage(firstMessage,objectSerializer)){
            if (isACompleteMessage(lastPreviousIncompleteMessage + firstMessage,objectSerializer)){
                //cout << "pruebo con: " << (lastPreviousIncompleteMessage + firstMessage) << endl;
                completeMessages.push_back((lastPreviousIncompleteMessage + firstMessage));
            }
        }

        for (auto partialMessage : partialMessages){
            if (isACompleteMessage(partialMessage,objectSerializer)){
                completeMessages.push_back(partialMessage);
            }
        }

        string lastMessage = partialMessages.at(partialMessages.size() -1);

        if (!isACompleteMessage(lastMessage,objectSerializer)){
            lastPreviousIncompleteMessage = lastMessage;
        }
    }
    //cout << "ahora mi ultimo es: " << (lastPreviousIncompleteMessage) << endl;

    return completeMessages;
}

void MessageParser::parse(string rawMessage, char separatorCharacter) {
    clear();
    lastParsedMessage = split(rawMessage,separatorCharacter);
}

MessageId MessageParser::getHeader() {

    if (lastParsedMessage != nullptr && !lastParsedMessage->empty()){
        return (MessageId)stoi(lastParsedMessage->at(1));
    }
    else {
        return UNDEFINED;
    }
}

string MessageParser::removePadding(char *buffer, char padding){

    int rawMessagelength = strlen(buffer);
    string extractedMessage = "";

    //limpio el padding
    //================================
    for (int i = 0; i < rawMessagelength; i++){
        if (buffer[i] != padding){
            extractedMessage += buffer[i];
        }
    }

    return extractedMessage;
}

void MessageParser::clear(){
    lastParsedMessage->clear();
}

//SPLIT
//=========================================================================================

vector<string> MessageParser::getPartialMessagesFrom(char* buffer, ObjectSerializer objectSerializer){

    vector<string> partialMessagesWithoutPadding;
    string partialMessageWithoutPadding = "";
    char prevCharRead = 0;

    char padding = objectSerializer.getPaddingSymbol();
    int buffLen = strlen(buffer);

    for (int i = 0; i < buffLen - 6; i++){
        if (buffer[i] != padding){
            if (prevCharRead != padding){
                partialMessageWithoutPadding += buffer[i];
            }
            else{
                partialMessageWithoutPadding = buffer[i];
            }
        }
        else{
            if (prevCharRead != padding){
                if (partialMessageWithoutPadding != ""){
                    partialMessagesWithoutPadding.push_back(partialMessageWithoutPadding);
                    partialMessageWithoutPadding = "";
                }
            }
        }
        prevCharRead = buffer[i];
    }
    partialMessagesWithoutPadding.push_back(partialMessageWithoutPadding);

    return partialMessagesWithoutPadding;
}

bool MessageParser::isACompleteMessage(string messageWithoutPadding, ObjectSerializer objectSerializer){

    //busco simbolo de start
    //================================
    int startSymbolIndex = 0;
    bool hasStartSymbol = false;
    for (int i = 0; i < strlen(messageWithoutPadding.c_str()); i++){
        if (messageWithoutPadding[i] == objectSerializer.getStartSerializationSymbol()){
            hasStartSymbol = true;
            startSymbolIndex = i;
            break;
        }
    }

    //busco simbolo de end
    //================================
    int endSymbolIndex = 0;
    bool hasEndSymbol = false;
    for (int i = 0; i < strlen(messageWithoutPadding.c_str()); i++){
        if (messageWithoutPadding[i] == objectSerializer.getEndOfSerializationSymbol()){
            hasEndSymbol = true;
            endSymbolIndex = i;
            break;
        }
    }

    if (hasStartSymbol && hasEndSymbol && startSymbolIndex < endSymbolIndex){
        return true;
    }
    else{
        return  false;
    }
}

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
