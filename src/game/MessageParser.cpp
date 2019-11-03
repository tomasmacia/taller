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
    lastParsedMessage = split(rawMessage,separatorCharacter);
}

MessageId MessageParser::getHeader() {

    if (!lastParsedMessage.empty()){
        return (MessageId)stoi(lastParsedMessage.at(0));
    }
    else UNDEFINED;
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

//SPLIT
//=========================================================================================
const vector<string> MessageParser::split(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
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
