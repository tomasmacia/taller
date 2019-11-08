//
// Created by axel on 1/11/19.
//

#ifndef GAME_MESSAGEPARSER_H
#define GAME_MESSAGEPARSER_H

#include "MessageId.h"
#include "ObjectSerializer.h"

using namespace std;


class MessageParser {

public:
    MessageParser();
    ~MessageParser();

    //API
    //===============================
    vector<string>& parse(string rawMessage, char separatorCharacter);
    string extractMeaningfulMessageFromStream(char *buffer, char endSerializationChar);
    void clear();
    MessageId getHeader();

    //GETTERS
    //===============================
    vector<string>& getCurrent(){
        return lastParsedMessage;
    }

private:
    //SPLIT
    //===============================
    vector<string> split(const string &s, const char &c);


    //ATRIBUTES
    //===============================
    vector<string> lastParsedMessage;
};


#endif //GAME_MESSAGEPARSER_H
