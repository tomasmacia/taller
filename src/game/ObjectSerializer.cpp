//
// Created by axel on 1/11/19.
//
#include <vector>
#include <iostream>
#include "ObjectSerializer.h"
#include "ToClientPack.h"
#include "MessageId.h"
#include "MessageParser.h"

using namespace std;

int ObjectSerializer::contador = 0;
int ObjectSerializer::contadorFail = 0;

//API
//=========================================================================================
int ObjectSerializer::getIDFrom(vector<string>* currentParsedMessage){
    return stoi(currentParsedMessage->at(2));
}

string ObjectSerializer::getUserFrom(vector<string>* currentParsedMessage){
    return currentParsedMessage->at(2);
}

string ObjectSerializer::getPassFrom(vector<string>* currentParsedMessage){
    return currentParsedMessage->at(3);
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
    //SERIALIZED LOGIN ID: //START,header,id
    return  currentParsedMessage->size() == 3 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
            (currentParsedMessage->at(1) == to_string(SUCCESS)
             || currentParsedMessage->at(1) == to_string(INVALID_CREDENTIAL)
             || currentParsedMessage->at(1) == to_string(ALREADY_LOGGED_IN_CREDENTIAL)
             || currentParsedMessage->at(1) == to_string(SERVER_FULL));
}

bool ObjectSerializer::validSerializedObjectMessage(vector<string>* currentParsedMessage){
    //SERIALIZED OBJECT: START, header,path,srcw,srch,srcx,srcy,dstw,dsth,dstx,dsty,bool
    return currentParsedMessage->size() == 12 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
            currentParsedMessage->at(1) == to_string(RENDERABLE);
}

bool ObjectSerializer::validSerializedSetOfObjectsMessage(vector<string>* serializedObjects){
    return !serializedObjects->empty() && serializedObjects->at(0) == to_string(SET_OF_RENDERABLES);
}

bool ObjectSerializer::validLoginFromClientMessage(vector<string>* currentParsedMessage) {
    //SERIALIZED LOGIN ID: START, header,user,pass
    return currentParsedMessage->size() == 4 &&
        currentParsedMessage->at(0) == START_SYMBOL &&
           (currentParsedMessage->at(1)) == to_string(USER_PASS);
}

bool ObjectSerializer::validSerializedInputMessage(vector<string>* currentParsedMessage){
    //SERIALIZED OBJECT: START,header,action,id
    return currentParsedMessage->size() == 4 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
           (currentParsedMessage->at(1)) == to_string(INPUT);
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

    return  new ToClientPack(path, src, dst, flip);
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

void ObjectSerializer::reconstructRenderables(vector<string>* serializedPackages, std::list<ToClientPack*>* renderables){

    MessageParser parser = MessageParser();

    for (int i = 1; i < serializedPackages->size(); i++){                            // i empieza en 1 porque el 0 contiene el header
        parser.parse(serializedPackages->at(i),SEPARATOR.c_str()[0]);
        if (validSerializedObjectMessage(parser.getCurrent())){
            renderables->push_back(reconstructRenderable(parser.getCurrent()));
        }
    }
}

//SERIALIZATION
//=========================================================================================

string ObjectSerializer::serializedSuccesfullLoginMessage(int id){
    return addPadding(START_SYMBOL + SEPARATOR + to_string(SUCCESS) + SEPARATOR + to_string(id) + END_OF_SERIALIZATION_SYMBOL);
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
    return addPadding(START_SYMBOL + SEPARATOR + to_string(USER_PASS) + SEPARATOR + user + SEPARATOR + pass + SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::getPingMessage(){
    return PING_CODE + END_OF_SERIALIZATION_SYMBOL;
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
                       flipedStr;

    return serializedObject;
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

std::string ObjectSerializer::serializeObjects(std::list<ToClientPack*>* packages){

    string serializedPackages = "";

    for (auto package : *packages){
        serializedPackages +=  serializeObject(package) + OBJECT_SEPARATOR_SYMBOL;
    }
    return addPadding(to_string(SET_OF_RENDERABLES) + OBJECT_SEPARATOR_SYMBOL + serializedPackages + END_OF_SERIALIZATION_SYMBOL);
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