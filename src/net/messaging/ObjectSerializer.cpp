//
// Created by axel on 1/11/19.
//
#include <vector>
#include <iostream>
#include "ObjectSerializer.h"
#include "Renderable.h"
#include "../../enumerates/MessageId.h"
#include "MessageParser.h"

using namespace std;

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

string ObjectSerializer::getSuccesfullLoginMessage(string color, int id){
    return serializedSuccesfullLoginMessage(color, id);
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
bool ObjectSerializer::validSerializedTestModeMessage(vector<string> *currentParsedMessage) {
    //SERIALIZED OBJECT: START,header,action,type
    return currentParsedMessage->size() == 4 &&
           currentParsedMessage->at(0) == START_SYMBOL &&
           currentParsedMessage->at(1)== to_string(INPUT) &&
           currentParsedMessage->at(2) == "TEST";
}

bool ObjectSerializer::validGameStartedMessage(vector<string> *currentParsedMessage) {
    //SERIALIZED LOGIN ID: //START,header
    return  currentParsedMessage->size() == 2 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
            currentParsedMessage->at(1) == to_string(GAME_STARTED);
}

bool ObjectSerializer::validPlayerDiedMessage(vector<string> *currentParsedMessage) {
    //SERIALIZED LOGIN ID: //START,header,id
    return  currentParsedMessage->size() == 3 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
            currentParsedMessage->at(1) == to_string(PLAYER_DIED);
}


bool ObjectSerializer::validEndOfGameMessage(vector<string> *currentParsedMessage) {
    //SERIALIZED LOGIN ID: //START,header
    return  currentParsedMessage->size() == 2 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
            currentParsedMessage->at(1) == to_string(END);
}

bool ObjectSerializer::validLoginFromServerMessage(vector<string>* currentParsedMessage){
    //SERIALIZED LOGIN ID: //START,header,type,color
    return  (currentParsedMessage->size() == 4 || currentParsedMessage->size() == 3) &&
            currentParsedMessage->at(0) == START_SYMBOL &&
            (currentParsedMessage->at(1) == to_string(SUCCESS)
             || currentParsedMessage->at(1) == to_string(INVALID_CREDENTIAL)
             || currentParsedMessage->at(1) == to_string(ALREADY_LOGGED_IN_CREDENTIAL)
             || currentParsedMessage->at(1) == to_string(SERVER_FULL));
}

bool ObjectSerializer::validSerializedObjectMessage(vector<string>* currentParsedMessage){
    //SERIALIZED OBJECT: START,header,path,srcw,srch,srcx,srcy,dstw,dsth,dstx,dsty,bool,header2,pathSound,isMusicBool
    return (currentParsedMessage->size() == 15 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
            currentParsedMessage->at(1) == to_string(RENDERABLE) &&
            currentParsedMessage->at(12) == to_string(SOUNDABLE)) ||
            (currentParsedMessage->size() == 12 &&
             currentParsedMessage->at(0) == START_SYMBOL &&
             currentParsedMessage->at(1) == to_string(RENDERABLE)) ||
            (currentParsedMessage->size() == 3 &&
             currentParsedMessage->at(0) == START_SYMBOL &&
             currentParsedMessage->at(1) == to_string(SOUNDABLE));
}

bool ObjectSerializer::validSerializedSetOfObjectsMessage(vector<string>* serializedObjects){
    return serializedObjects->size() > 1 && serializedObjects->at(0) == START_SYMBOL && serializedObjects->at(1) == to_string(SET_OF_SENDABLES);
}

bool ObjectSerializer::validLoginFromClientMessage(vector<string>* currentParsedMessage) {
    //SERIALIZED LOGIN ID: START, header,user,pass
    return currentParsedMessage->size() == 4 &&
        currentParsedMessage->at(0) == START_SYMBOL &&
           (currentParsedMessage->at(1)) == to_string(USER_PASS);
}

bool ObjectSerializer::validSerializedInputMessage(vector<string>* currentParsedMessage){
    //SERIALIZED OBJECT: START,header,action,type
    return currentParsedMessage->size() == 4 &&
            currentParsedMessage->at(0) == START_SYMBOL &&
           (currentParsedMessage->at(1)) == to_string(INPUT);
}

//RECONSTRUCT
//=========================================================================================

Sendable* ObjectSerializer::reconstructSendable(vector<string>* currentParsedMessage) {

    Renderable* renderable = nullptr;
    Soundable* soundable = nullptr;

    if (currentParsedMessage->size() > 0) {

        if (currentParsedMessage->at(1) == to_string(RENDERABLE)){

            std::string path = resourcesUtils->getResource(stoi(currentParsedMessage->at(2)));
            Rect src = {std::stoi(currentParsedMessage->at(5)), std::stoi(currentParsedMessage->at(6)),
                        std::stoi(currentParsedMessage->at(3)),
                        std::stoi(currentParsedMessage->at(4))};
            Rect dst = {std::stoi(currentParsedMessage->at(9)), std::stoi(currentParsedMessage->at(10)),
                        std::stoi(currentParsedMessage->at(7)),
                        std::stoi(currentParsedMessage->at(8))};
            bool flip = std::stoi(currentParsedMessage->at(11));

            renderable = new Renderable(path, src, dst, flip);

            if (currentParsedMessage->size() == 15) {

                string soundPath = currentParsedMessage->at(13);
                bool isMusic = std::stoi(currentParsedMessage->at(14));

                soundable = new Soundable(soundPath, isMusic);
            }
        }

        if (currentParsedMessage->at(1) == to_string(SOUNDABLE)){

            string soundPath = currentParsedMessage->at(2);
            bool isMusic = std::stoi(currentParsedMessage->at(3));

            soundable = new Soundable(soundPath, isMusic);
        }

        return new Sendable(renderable, soundable);
    }

    return nullptr;
}

tuple<Action,int> ObjectSerializer::reconstructInput(vector<string>* currentParsedMessage) {

    string action = currentParsedMessage->at(2);
    int reconstructedId = std::stoi(currentParsedMessage->at(3));

    Action reconstructedAction;
    if (action == "NONE"){reconstructedAction = NONE;}
    if (action == "UP"){reconstructedAction = UP;}
    if (action == "END_UP"){reconstructedAction = END_UP;}
    if (action == "DOWN"){reconstructedAction = DOWN;}
    if (action == "END_DOWN"){reconstructedAction = END_DOWN;}
    if (action == "LEFT"){reconstructedAction = LEFT;}
    if (action == "END_LEFT"){reconstructedAction = END_LEFT;}
    if (action == "RIGHT"){reconstructedAction = RIGHT;}
    if (action == "END_RIGHT"){reconstructedAction = END_RIGHT;}
    if (action == "JUMP"){reconstructedAction = JUMP;}
    if (action == "PUNCH"){reconstructedAction = PUNCH;}
    if (action == "KICK"){reconstructedAction = KICK;}
    if (action == "JUMP_KICK"){reconstructedAction = JUMP_KICK;}
    if (action == "CROUCH"){reconstructedAction = CROUCH;}
    if (action == "TEST"){reconstructedAction = TEST;}

    return make_tuple (reconstructedAction,reconstructedId);
}

void ObjectSerializer::reconstructSendables(vector<string>* serializedPackages, std::list<Sendable*>* reconstructedPackages){

    MessageParser parser = MessageParser();

    for (int i = 2; i < serializedPackages->size(); i++){                            // i empieza en 2 porque el 0 y 1 contiene el header
        parser.parse(serializedPackages->at(i),SEPARATOR.c_str()[0]);
        if (validSerializedObjectMessage(parser.getCurrent())){
            reconstructedPackages->push_back(reconstructSendable(parser.getCurrent()));
        }
    }
}

//SERIALIZATION
//=========================================================================================
string ObjectSerializer::getGameStartedMessage() {
    return addPadding(START_SYMBOL + SEPARATOR + to_string(GAME_STARTED) + SEPARATOR +  END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::getPlayerDiedMessage(int id) {
    return addPadding(START_SYMBOL + SEPARATOR + to_string(PLAYER_DIED) + SEPARATOR + to_string(id) + SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::getEndOfGameMessage() {
    return addPadding(START_SYMBOL + SEPARATOR + to_string(END) + SEPARATOR +  END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::serializedSuccesfullLoginMessage(string color, int id){
    return addPadding(START_SYMBOL + SEPARATOR + to_string(SUCCESS) + SEPARATOR + to_string(id) + SEPARATOR + color + SEPARATOR +  END_OF_SERIALIZATION_SYMBOL);
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
    return START_SYMBOL + PING_CODE + END_OF_SERIALIZATION_SYMBOL;
}

string ObjectSerializer::getParsedPingMessage(){
    return START_SYMBOL + PING_CODE;
}

string ObjectSerializer::serializeInput(Action action, int id){

    std::string  serializedAction;

    if (action == NONE){serializedAction = "NONE";}
    if (action == UP){serializedAction = "UP";}
    if (action == END_UP){serializedAction = "END_UP";}
    if (action == DOWN){serializedAction = "DOWN";}
    if (action == END_DOWN){serializedAction = "END_DOWN";}
    if (action == LEFT){serializedAction = "LEFT";}
    if (action == END_LEFT){serializedAction = "END_LEFT";}
    if (action == RIGHT){serializedAction = "RIGHT";}
    if (action == END_RIGHT){serializedAction = "END_RIGHT";}
    if (action == JUMP){serializedAction = "JUMP";}
    if (action == PUNCH){serializedAction = "PUNCH";}
    if (action == KICK){serializedAction = "KICK";}
    if (action == JUMP_KICK){serializedAction = "JUMP_KICK";}
    if (action == CROUCH){serializedAction = "CROUCH";}
    if (action == TEST){serializedAction = "TEST";}

    return addPadding(START_SYMBOL + SEPARATOR  + to_string(INPUT) + SEPARATOR + serializedAction + SEPARATOR + to_string(id) + SEPARATOR + END_OF_SERIALIZATION_SYMBOL);
}

string ObjectSerializer::serializeObject(Sendable* sendable){

    std::string serializedObject;
    std::string serializedRenderable;
    std::string serializedSoundable;

    auto soundable = sendable->_soundable;
    auto renderable = sendable->_renderable;

    if (sendable == nullptr){
        return "";
    }

    if (renderable != nullptr){

        std::string path = to_string(resourcesUtils->getId(renderable->getPath()));
        Rect src = renderable->getSrcRect();
        Rect dst = renderable->getDstRect();
        bool fliped = renderable->getFliped();

        std::string srcW = to_string(src.w);
        std::string srcH = to_string(src.h);
        std::string srcX = to_string(src.x);
        std::string srcY = to_string(src.y);

        std::string dstW = to_string(dst.w);
        std::string dstH = to_string(dst.h);
        std::string dstX = to_string(dst.x);
        std::string dstY = to_string(dst.y);

        std::string flipedStr = to_string(fliped);

        serializedRenderable = to_string(RENDERABLE) + SEPARATOR + path + SEPARATOR +
                               srcW + SEPARATOR + srcH + SEPARATOR + srcX + SEPARATOR + srcY + SEPARATOR +
                               dstW + SEPARATOR + dstH + SEPARATOR + dstX + SEPARATOR + dstY + SEPARATOR +
                               flipedStr;
    }

    if(soundable != nullptr){

        std::string strIsMusic = to_string(soundable->getBoolMusic());
        std::string strPath = soundable->getPath();

        serializedSoundable = to_string(SOUNDABLE) + SEPARATOR + strPath + SEPARATOR + strIsMusic;
    }

    serializedObject = START_SYMBOL + SEPARATOR +  serializedRenderable + SEPARATOR + serializedSoundable;

    return serializedObject;
}

std::string ObjectSerializer::serializeObjects(std::list<Sendable*>* sendables){

    string serializedPackages = "";

    int i = 0;
    for (auto sendable : *sendables){
        serializedPackages += serializeObject(sendable) + OBJECT_SEPARATOR_SYMBOL;
        i++;
    }
    return addPadding(START_SYMBOL + OBJECT_SEPARATOR_SYMBOL + to_string(SET_OF_SENDABLES) + OBJECT_SEPARATOR_SYMBOL + serializedPackages + END_OF_SERIALIZATION_SYMBOL);
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
