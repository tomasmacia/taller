//
// Created by axel on 1/11/19.
//
#include <vector>
#include <iostream>
#include "ObjectSerializer.h"
#include "ToClientPack.h"
#include "MessageId.h"

using namespace std;

//API
//=========================================================================================
int ObjectSerializer::getIDFrom(vector<string>* currentParsedMessage){
    return stoi(currentParsedMessage->at(1));
}

string ObjectSerializer::getUserFrom(vector<string>* currentParsedMessage){
    return currentParsedMessage->at(1);
}

string ObjectSerializer::getPassFrom(vector<string>* currentParsedMessage){
    return currentParsedMessage->at(2);
}

string ObjectSerializer::getSuccesfullLoginMessage(int id){
    return serializedSuccesfullLoginMessage(id);
}

string ObjectSerializer::getInvalidCredentialMessage(){
    return serializedInvalidCredentialMessage();
}

string ObjectSerializer::getServerFullMessage(){
    return serializedServerFullMessage();
}

string ObjectSerializer::getAlreadyLoggedInMessage() {
    return serializedAlreadyLoggedInMessage();
}

//VALIDATE
//=========================================================================================
bool ObjectSerializer::validLoginFromServerMessage(vector<string>* currentParsedMessage){
    //SERIALIZED LOGIN ID: //START,header,id,END
    return currentParsedMessage->size() == 4 &&
            currentParsedMessage->at(0) == START_SYMBOL
           && (stoi(currentParsedMessage->at(1)) == SUCCESS
           ||   stoi(currentParsedMessage->at(1)) == INVALID_CREDENTIAL
           ||   stoi(currentParsedMessage->at(1)) == ALREADY_LOGGED_IN_CREDENTIAL
           ||   stoi(currentParsedMessage->at(1)) == SERVER_FULL)
           && currentParsedMessage->at(currentParsedMessage->size() - 1) == END_OF_SERIALIZATION_SYMBOL;
}

bool ObjectSerializer::validSerializedObjectMessage(vector<string>* currentParsedMessage){
    //SERIALIZED OBJECT: START,header,path,srcw,srch,srcx,srcy,dstw,dsth,dstx,dsty,bool,END
    return currentParsedMessage->size() == 13 &&
            currentParsedMessage->at(0) == START_SYMBOL
           && stoi(currentParsedMessage->at(1)) == RENDERABLE
           && currentParsedMessage->at(currentParsedMessage->size() - 1) == END_OF_SERIALIZATION_SYMBOL;
}

bool ObjectSerializer::validLoginFromClientMessage(vector<string>* currentParsedMessage) {
    //SERIALIZED LOGIN ID: START, header,user,pass,END
    return currentParsedMessage->size() == 5 &&
            currentParsedMessage->at(0) == START_SYMBOL
           && stoi(currentParsedMessage->at(1)) == USER_PASS
           && currentParsedMessage->at(currentParsedMessage->size() - 1) == END_OF_SERIALIZATION_SYMBOL;
}

bool ObjectSerializer::validSerializedInputMessage(vector<string>* currentParsedMessage){
    //SERIALIZED OBJECT: START,header,action,id,END
    return  currentParsedMessage->size() == 5 &&
            currentParsedMessage->at(0) == START_SYMBOL
            && stoi(currentParsedMessage->at(1)) == INPUT
            && currentParsedMessage->at(currentParsedMessage->size() - 1) == END_OF_SERIALIZATION_SYMBOL;
}

//RECONSTRUCT
//=========================================================================================

ToClientPack* ObjectSerializer::reconstructRenderable(vector<string>* currentParsedMessage) {

    std::string path = currentParsedMessage->at(2);
    SDL_Rect src = {std::stoi(currentParsedMessage->at(5)), std::stoi(currentParsedMessage->at(6)), std::stoi(currentParsedMessage->at(3)),
                    std::stoi(currentParsedMessage->at(4))};
    SDL_Rect dst = {std::stoi(currentParsedMessage->at(9)), std::stoi(currentParsedMessage->at(10)), std::stoi(currentParsedMessage->at(7)),
                    std::stoi(currentParsedMessage->at(8))};
    bool flip = std::stoi(currentParsedMessage->at(11));

    return  new ToClientPack(path, src, dst, flip);;
}

tuple<Action,int> ObjectSerializer::reconstructInput(vector<string>* currentParsedMessage) {

    string action = currentParsedMessage->at(2);
    int reconstructedId = std::stoi(currentParsedMessage->at(3));

    Action reconstructedAction;
    if (action == "NONE"){reconstructedAction = NONE;}
    if (action == "UP"){reconstructedAction = UP;}
    if (action == "DOWN"){reconstructedAction = DOWN;}
    if (action == "LEFT"){reconstructedAction = LEFT;}
    if (action == "RIGHT"){reconstructedAction = RIGHT;}
    if (action == "JUMP"){reconstructedAction = JUMP;}
    if (action == "PUNCH"){reconstructedAction = PUNCH;}
    if (action == "KICK"){reconstructedAction = KICK;}
    if (action == "JUMP_KICK"){reconstructedAction = JUMP_KICK;}
    if (action == "CROUCH"){reconstructedAction = CROUCH;}

    return make_tuple (reconstructedAction,reconstructedId);
}

//SERIALIZATION
//=========================================================================================

string ObjectSerializer::serializedSuccesfullLoginMessage(int id){
    return addPadding(START_SYMBOL + SEPARATOR + to_string(SUCCESS) + SEPARATOR + to_string(id) +
    SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::serializedInvalidCredentialMessage(){
    return addPadding(START_SYMBOL + SEPARATOR + to_string(INVALID_CREDENTIAL) + SEPARATOR + to_string(FAILURE_AKNOWLEDGE_SIGNAL) + SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::serializedServerFullMessage(){
    return addPadding(START_SYMBOL + SEPARATOR + to_string(SERVER_FULL) + SEPARATOR + to_string(FAILURE_AKNOWLEDGE_SIGNAL) + SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::serializedAlreadyLoggedInMessage(){
    return addPadding(START_SYMBOL + SEPARATOR + to_string(ALREADY_LOGGED_IN_CREDENTIAL) + SEPARATOR + to_string(FAILURE_AKNOWLEDGE_SIGNAL) + SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::serializeCredentials(string user, string pass){
    return addPadding(START_SYMBOL + SEPARATOR + to_string(USER_PASS) + SEPARATOR + user + SEPARATOR + pass + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::serializeObject(ToClientPack* package){

    std::string serializedObject;

    std::string path = package->getPath();
    SDL_Rect src = package->getSrcRect();
    SDL_Rect dst = package->getDstRect();
    bool fliped = package->getFliped();

    std::string srcW = to_string(src.w);
    std::string srcH = to_string(src.h);
    std::string srcX = to_string(src.x);
    std::string srcY = to_string(src.y);

    std::string dstW = to_string(dst.w);
    std::string dstH = to_string(dst.h);
    std::string dstX = to_string(dst.x);
    std::string dstY = to_string(dst.y);

    std::string flipedStr = to_string(fliped);

    serializedObject = START_SYMBOL + SEPARATOR + to_string(RENDERABLE) + SEPARATOR + path + SEPARATOR +
                       srcW + SEPARATOR + srcH + SEPARATOR + srcX + SEPARATOR + srcY + SEPARATOR +
                       dstW + SEPARATOR + dstH + SEPARATOR + dstX + SEPARATOR + dstY + SEPARATOR +
                       flipedStr + SEPARATOR + END_OF_SERIALIZATION_SYMBOL;

    return addPadding(serializedObject);
}

string ObjectSerializer::serializeInput(Action action, int id){

    std::string  serializedAction;

    if (action == NONE){serializedAction = "NONE";}
    if (action == UP){serializedAction = "UP";}
    if (action == DOWN){serializedAction = "DOWN";}
    if (action == LEFT){serializedAction = "LEFT";}
    if (action == RIGHT){serializedAction = "RIGHT";}
    if (action == JUMP){serializedAction = "JUMP";}
    if (action == PUNCH){serializedAction = "PUNCH";}
    if (action == KICK){serializedAction = "KICK";}
    if (action == JUMP_KICK){serializedAction = "JUMP_KICK";}
    if (action == CROUCH){serializedAction = "CROUCH";}

    return addPadding(START_SYMBOL + SEPARATOR  + to_string(INPUT) + SEPARATOR + serializedAction + SEPARATOR + to_string(id) + SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::addPadding(string message){

    string messageToSend = message;
    int messageLength = strlen(message.c_str());
    int amountOfPaddingToAdd = totalMessageLength - messageLength;

    for (int i = 0; i < amountOfPaddingToAdd; i++){
        messageToSend += PADDING_SYMBOL;
    }

    return messageToSend;
}