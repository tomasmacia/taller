//
// Created by axel on 1/11/19.
//

#ifndef GAME_MESSAGEPARSER_H
#define GAME_MESSAGEPARSER_H

#include "MessageId.h"

using namespace std;


class MessageParser {

public:

    //API
    //===============================
    void parse(string rawMessage, char separatorCharacter);
    MessageId getHeader();
    string extractMeaningfulMessageFromStream(char *buffer, char separator, char endSerializationChar);

    //API
    //===============================
    vector<string> getCurrent(){
        return lastParsedMessage;
    }

private:
    //SPLIT
    //===============================
    const vector<string> split(const string &s, const char &c);


    //ATRIBUTES
    //===============================
    vector<string> lastParsedMessage;
};


#endif //GAME_MESSAGEPARSER_H
