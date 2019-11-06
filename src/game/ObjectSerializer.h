//
// Created by axel on 1/11/19.
//

#ifndef GAME_OBJECTSERIALIZER_H
#define GAME_OBJECTSERIALIZER_H

#include <string>
#include <list>
#include "ToClientPack.h"
#include "Action.h"
#include "MessageId.h"

using namespace std;


class ObjectSerializer {

public:

    //API
    //===============================
    int getIDFrom(vector<string>* currentParsedMessage);
    string getUserFrom(vector<string>* currentParsedMessage);
    string getPassFrom(vector<string>* currentParsedMessage);
    std::string getSuccesfullLoginMessage(int userId);
    std::string getInvalidCredentialMessage();
    std::string getServerFullMessage();
    std::string getAlreadyLoggedInMessage();
    std::string serializeObjects(std::list<ToClientPack*>* packages);

    //VALIDATE
    //===============================
    bool validLoginFromServerMessage(vector<string>* currentParsedMessage);
    bool validSerializedObjectMessage(vector<string>* currentParsedMessage);
    bool validLoginFromClientMessage(vector<string>* currentParsedMessage);
    bool validSerializedInputMessage(vector<string>* currentParsedMessage);

    //RECONSTRUCT
    //===============================
    ToClientPack* reconstructRenderable(vector<string>* currentParsedMessage);
    tuple<Action,int> reconstructInput(vector<string>* currentParsedMessage);
    void reconstructRenderables(string serializedPackages, std::list<ToClientPack*>* renderables);

    //SERIALIZATION
    //===============================
    std::string serializedSuccesfullLoginMessage(int userId);
    std::string serializedInvalidCredentialMessage();
    std::string serializedServerFullMessage();
    std::string serializedAlreadyLoggedInMessage();
    string serializeObject(ToClientPack* package);
    string serializeInput(Action action, int id);
    string serializeCredentials(string user, string pass);
    string addPadding(string message);

    //GETTERS
    //===============================
    int getTotalMessageLength(){
        return totalMessageLength;
    }

    string getFailure(){
        return FAILURE;
    }

    string getPingCode(){
        return PING_CODE + string(totalMessageLength - PING_CODE.length(),END_SERIALIZATION_SIMBOL);
    }


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
    string PING_CODE = "###";
    char END_SERIALIZATION_SIMBOL = '*';
    char OBJECT_SEPARATOR_SYMBOL = '%';
    char SEPARATOR = '@';
    int FAILURE_AKNOWLEDGE_SIGNAL = -1;
    string FAILURE = "-1";
    int totalMessageLength = 3000;

    static int contador;
    static int contadorFail;

};


#endif //GAME_OBJECTSERIALIZER_H
