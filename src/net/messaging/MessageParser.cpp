//
// Created by axel on 1/11/19.
//

#include <vector>
#include <string>
#include <cstring>
#include <list>
#include <iostream>

#include "../../enumerates/MessageId.h"
#include "MessageParser.h"

using namespace std;

//API
//=========================================================================================
vector<string>* MessageParser::parse(string rawMessage, char separatorCharacter) {
    clear();
    lastParsedMessage = split(rawMessage,separatorCharacter);
    return lastParsedMessage;
}

string MessageParser::extractMeaningfulMessageFromStream(char *buffer, int bufferLength, string failureMessage,
                                                         char startSerializationSymbol, char endSerializationChar, char padding){

    string extractedMessage = "";
    bool hasReadStartSymbol = false;

    for (int i = 0; i < bufferLength; i++){
        if (buffer[i] == startSerializationSymbol){
            hasReadStartSymbol = true;
        }
    }

    if (hasReadStartSymbol){
        int i = 0;
        while (buffer[i] != endSerializationChar){

            if (buffer[i] != padding){
                extractedMessage += buffer[i];
            }
            if (i == bufferLength){
                break;
            }
            i++;
        }

        if (buffer[i] == endSerializationChar){
            return extractedMessage;
        }
    }
    else{
        return failureMessage;
    }
}

void MessageParser::clear(){
    lastParsedMessage->clear();
}

MessageId MessageParser::getHeader(){
   if (lastParsedMessage != nullptr && lastParsedMessage->size() > 2){
       return (MessageId)std::stoi(lastParsedMessage->at(1));
   }
   else{
       return UNDEFINED;
   }
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
    lastParsedMessage = new vector<string>();
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
