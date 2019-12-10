//
// Created by axel on 1/11/19.
//

#ifndef GAME_OBJECTSERIALIZER_H
#define GAME_OBJECTSERIALIZER_H

#include <string>
#include <list>
#include "Renderable.h"
#include "Sendable.h"
#include "../../enumerates/Action.h"
#include "../../enumerates/MessageId.h"

using namespace std;


class ObjectSerializer {

public:

    //API
    //===============================
    int getIDFrom(vector<string>* currentParsedMessage);
    string getUserFrom(vector<string>* currentParsedMessage);
    string getPassFrom(vector<string>* currentParsedMessage);
    std::string getSuccesfullLoginMessage(string color, int userId);
    std::string getInvalidCredentialMessage();
    std::string getServerFullMessage();
    std::string getAlreadyLoggedInMessage();
    std::string serializeObjects(std::list<Sendable*>* sendables);

    //VALIDATE
    //===============================
    bool validLoginFromServerMessage(vector<string>* currentParsedMessage);
    bool validSerializedObjectMessage(vector<string>* currentParsedMessage);
    bool validSerializedSetOfObjectsMessage(vector<string>* currentParsedMessage);
    bool validLoginFromClientMessage(vector<string>* currentParsedMessage);
    bool validSerializedInputMessage(vector<string>* currentParsedMessage);

    //RECONSTRUCT
    //===============================
    Sendable* reconstructSendable(vector<string>* currentParsedMessage);
    tuple<Action,int> reconstructInput(vector<string>* currentParsedMessage);
    void reconstructSendables(vector<string>* serializedPackages, std::list<Sendable*>* sendables);

    //SERIALIZATION
    //===============================
    std::string serializedSuccesfullLoginMessage(string color, int userId);
    std::string serializedInvalidCredentialMessage();
    std::string serializedServerFullMessage();
    std::string serializedAlreadyLoggedInMessage();
    string serializeObject(Sendable* sendable);
    string serializeInput(Action action, int id);
    string serializeCredentials(string user, string pass);
    string getPingMessage();
    string addPadding(string message);

    //GETTERS
    //===============================
    char getObjectSeparator(){
        return OBJECT_SEPARATOR_SYMBOL;
    }

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
        return PING_CODE;
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
    string END_OF_SERIALIZATION_SYMBOL = "&";
    string PING_CODE = "###";
    char OBJECT_SEPARATOR_SYMBOL = '%';
    char PADDING_SYMBOL = '*';
    string SEPARATOR = "@";
    int FAILURE_AKNOWLEDGE_SIGNAL = -1;
    string START_SYMBOL = "=";
    string FAILURE = "-1";
    int totalMessageLength = 1500;
    string END_OF_RENDERABLE_SYMBOL = "|";



    static int contador;
    static int contadorFail;


};


#endif //GAME_OBJECTSERIALIZER_H
