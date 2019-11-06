//
// Created by axel on 1/11/19.
//

#ifndef GAME_MESSAGEPARSER_H
#define GAME_MESSAGEPARSER_H

#include "MessageId.h"

using namespace std;


class MessageParser {

public:
    MessageParser();
    ~MessageParser();

    //API
    //===============================
    void parse(string rawMessage, char separatorCharacter);
    void parseModel(string rawMessage, char separatorCharacter, char separatorGameObjectCharacter);
    MessageId getHeader();
    string extractMeaningfulMessageFromStream(char *buffer, char endSerializationChar);
    vector<string> extractMeaningfulMessagesFromStream(char *buffer, char endSerializationChar);
    void clear();

    //GETTERS
    //===============================
    vector<string>* getCurrent(){
        return lastParsedMessage;
    }

    vector<vector<string>>* lastParsedMessages = nullptr;

private:
    //SPLIT
    //===============================
    vector<string>* split(const string &s, const char &c);


    //ATRIBUTES
    //===============================
    vector<string>* lastParsedMessage = nullptr;
};


#endif //GAME_MESSAGEPARSER_H
