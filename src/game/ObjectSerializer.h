//
// Created by axel on 1/11/19.
//

#ifndef GAME_OBJECTSERIALIZER_H
#define GAME_OBJECTSERIALIZER_H

#include <string>
#include "ToClientPack.h"
#include "Action.h"
#include "MessageId.h"

using namespace std;


class ObjectSerializer {

public:

    //API
    //===============================
    int getIDFrom(vector<string> currentParsedMessage);
    string getUserFrom(vector<string> currentParsedMessage);
    string getPassFrom(vector<string> currentParsedMessage);
    std::string getSuccesfullLoginMessage(int userId);
    std::string getInvalidCredentialMessage();
    std::string getServerFullMessage();
    std::string getAlreadyLoggedInMessage();

    //VALIDATE
    //===============================
    bool validLoginFromServerMessage(vector<string> currentParsedMessage);
    bool validSerializedObjectMessage(vector<string> currentParsedMessage);
    bool validLoginFromClientMessage(vector<string> currentParsedMessage);
    bool validSerializedInputMessage(vector<string> currentParsedMessage);

    //RECONSTRUCT
    //===============================
    ToClientPack reconstructRenderable(vector<string> currentParsedMessage);
    tuple<Action,int> reconstructInput(vector<string> currentParsedMessage);

    //SERIALIZE
    //===============================
    string serializeObject(ToClientPack package);
    string serializeInput(Action action, int id);

    //GETTERS
    //===============================
    char getSeparatorCharacter(){
        return SEPARATOR;
    }

    int getFailureAcknowledgeSignal(){
        return FAILURE_AKNOWLEDGE_SIGNAL;
    }

    char getEndOfSerializationCharacterget(){
        return END_SERIALIZATION_SIMBOL;
    }

private:
    char END_SERIALIZATION_SIMBOL = 'x';
    char SEPARATOR = '@';
    int FAILURE_AKNOWLEDGE_SIGNAL = -1;

};


#endif //GAME_OBJECTSERIALIZER_H
