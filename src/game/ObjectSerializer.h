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
    int getIDFrom(vector<string>* currentParsedMessage);
    string getUserFrom(vector<string>* currentParsedMessage);
    string getPassFrom(vector<string>* currentParsedMessage);
    std::string getSuccesfullLoginMessage(int userId);
    std::string getInvalidCredentialMessage();
    std::string getServerFullMessage();
    std::string getAlreadyLoggedInMessage();

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
    char getStartSerializationSymbol(){
        return START_SYMBOL.c_str()[0];
    }

    char getPaddingSymbol(){
        return PADDING_SYMBOL;
    }

    int getTotalMessageLength(){
        return totalMessageLength;
    }

    string getFailure(){
        return FAILURE;
    }

    string getPingCode(){
        return PING_CODE + string(totalMessageLength - PING_CODE.length(),'&'); // TODO HARDCODE
    }


    char getSeparatorCharacter(){
        return SEPARATOR.c_str()[0];
    }

    int getFailureAcknowledgeSignal(){
        return FAILURE_AKNOWLEDGE_SIGNAL;
    }

    char getEndOfSerializationSymbol(){
        return END_OF_SERIALIZATION_SYMBOL.c_str()[0];
    }

private:
    string PING_CODE = "*";
    string END_OF_SERIALIZATION_SYMBOL = "&";
    char PADDING_SYMBOL = '*';
    string SEPARATOR = "@";
    int FAILURE_AKNOWLEDGE_SIGNAL = -1;
    string START_SYMBOL = "=";
    string FAILURE = "-1";
    int totalMessageLength = 128;

    static int contador;
    static int contadorFail;

};


#endif //GAME_OBJECTSERIALIZER_H
