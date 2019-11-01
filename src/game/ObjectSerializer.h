//
// Created by axel on 1/11/19.
//

#ifndef GAME_OBJECTSERIALIZER_H
#define GAME_OBJECTSERIALIZER_H

#include <string>

using namespace std;


class ObjectSerializer {

public:

    //API
    //===============================
    bool validLoginIDFromServerMessage(vector<string> currentParsedMessage);


    //GETTERS
    //===============================
    char getSeparatorCharacter(){
        return SEPARATOR;
    }

    int getFailureAcknowledgeSignal(){
        return FAILURE_AKNOWLEDGE_SIGNAL;
    }

private:
    string END_SERIALIZATION_SIMBOL ="x";
    char SEPARATOR = '_';
    int FAILURE_AKNOWLEDGE_SIGNAL = -1;

};


#endif //GAME_OBJECTSERIALIZER_H
