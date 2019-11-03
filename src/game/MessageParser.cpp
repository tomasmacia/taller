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
    return (MessageId)stoi(lastParsedMessage.at(0));
}

string MessageParser::extractMeaningfulMessageFromStream(char* buffer, char separator, char endSerializationChar){
    //cleans buffer up

    std::string stringedBuffer = buffer;

    if (stringedBuffer.empty()) {
        return stringedBuffer;
    }
    std::string delimiter = std::string(1, separator) + std::string(1, endSerializationChar);
    std::string message = stringedBuffer.substr(0, stringedBuffer.find(delimiter));

    //le quito al buffer lo que acabo de parsear
    int messageLength = message.length();
    std::string restOfBuffer = stringedBuffer.substr(stringedBuffer.find(delimiter),stringedBuffer.length() - messageLength);

    //(TODO) QUIZAS SEA COSTOSO A LA LARGA EN RECURSOS PORQUE SE HACE TODO EL TIEMPO ESTO
    char* cleanedBuf;
    strcpy(cleanedBuf, restOfBuffer.c_str());
    buffer = cleanedBuf;

    return message;
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
