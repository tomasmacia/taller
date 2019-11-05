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
    void parse(string rawMessage, char separatorCharacter);
    MessageId getHeader();
    vector<string> extractMeaningfulMessagesFromStream(char *buffer, ObjectSerializer objectSerializer);
    string removePadding(char *buffer, char padding);
    void clear();

    //GETTERS
    //===============================
    vector<string>* getCurrent(){
        return lastParsedMessage;
    }

private:
    //SPLIT
    //===============================
    vector<string>* split(const string &s, const char &c);
    vector<string> getPartialMessagesFrom(char* buffer, ObjectSerializer objectSerializer);
    bool isACompleteMessage(string message, ObjectSerializer objectSerializer);


    //ATRIBUTES
    //===============================
    vector<string>* lastParsedMessage = nullptr;

    string lastPreviousIncompleteMessage = "";
};


#endif //GAME_MESSAGEPARSER_H
