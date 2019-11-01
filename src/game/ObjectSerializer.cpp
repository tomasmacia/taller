//
// Created by axel on 1/11/19.
//
#include <vector>
#include "ObjectSerializer.h"
#include "ToClientPack.h"
#include "Header.h"

using namespace std;

//API
//=========================================================================================
int ObjectSerializer::getIDFrom(vector<string> currentParsedMessage){
    return stoi(currentParsedMessage.at(1));
}

string ObjectSerializer::getUserFrom(vector<string> currentParsedMessage){
    return currentParsedMessage.at(1);
}

string ObjectSerializer::getPassFrom(vector<string> currentParsedMessage){
    return currentParsedMessage.at(2);
}

string ObjectSerializer::getSuccesfullLoginMessage(int id){
    return to_string(LOGIN) + SEPARATOR + to_string(id) + SEPARATOR + END_SERIALIZATION_SIMBOL;
}

string ObjectSerializer::getFailedLoginMessage(){
    return to_string(LOGIN) + SEPARATOR + to_string(FAILURE_AKNOWLEDGE_SIGNAL) + SEPARATOR + to_string(END_SERIALIZATION_SIMBOL);
}

//VALIDATE
//=========================================================================================
bool ObjectSerializer::validLoginIDFromServerMessage(vector<string> currentParsedMessage){
    //SERIALIZED LOGIN ID: //header,id,END_SERIALIZATION_SIMBOL
    int id = stoi(currentParsedMessage.at(1));
    return currentParsedMessage.size() == 3 && id != -1;
}

bool ObjectSerializer::validSerializedObjectMessage(vector<string> currentParsedMessage){
    //SERIALIZED OBJECT: header,path,srcw,srch,srcx,srcy,dstw,dsth,dstx,dsty,bool,END_SERIALIZATION_SIMBOL
    return currentParsedMessage.size() == 12;
}

bool ObjectSerializer::validLoginFromClientMessage(vector<string> currentParsedMessage){
    //SERIALIZED LOGIN ID: header,user,pass,END_SERIALIZATION_SIMBOL
    return currentParsedMessage.size() == 4;
}

bool ObjectSerializer::validSerializedInputMessage(vector<string> currentParsedMessage){
    //SERIALIZED OBJECT: header,action,id,END_SERIALIZATION_SIMBOL
    return currentParsedMessage.size() == 4;
}

//RECONSTRUCT
//=========================================================================================

ToClientPack ObjectSerializer::reconstructRenderable(vector<string> currentParsedMessage) {

    std::string path = currentParsedMessage.at(1);
    SDL_Rect src = {std::stoi(currentParsedMessage.at(4)), std::stoi(currentParsedMessage.at(5)), std::stoi(currentParsedMessage.at(2)),
                    std::stoi(currentParsedMessage.at(3))};
    SDL_Rect dst = {std::stoi(currentParsedMessage.at(8)), std::stoi(currentParsedMessage.at(9)), std::stoi(currentParsedMessage.at(6)),
                    std::stoi(currentParsedMessage.at(7))};
    bool flip = std::stoi(currentParsedMessage.at(10));

    ToClientPack reconstructedPackage(path, src, dst, flip);
}

tuple<Action,int> ObjectSerializer::reconstructInput(vector<string> currentParsedMessage) {

    string action = currentParsedMessage.at(1);
    int reconstructedId = std::stoi(currentParsedMessage.at(2));

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

//SERIALIZE
//=========================================================================================
string ObjectSerializer::serializeObject(ToClientPack package){

    std::string serializedObject;

    std::string path = package.getPath();
    SDL_Rect src = package.getSrcRect();
    SDL_Rect dst = package.getDstRect();
    bool fliped = package.getFliped();

    std::string srcW = to_string(src.w);
    std::string srcH = to_string(src.h);
    std::string srcX = to_string(src.x);
    std::string srcY = to_string(src.y);

    std::string dstW = to_string(dst.w);
    std::string dstH = to_string(dst.h);
    std::string dstX = to_string(dst.x);
    std::string dstY = to_string(dst.y);

    std::string flipedStr = to_string(fliped);

    serializedObject = to_string(GAME) + SEPARATOR + path + SEPARATOR +
                       srcW + SEPARATOR + srcH + SEPARATOR + srcX + SEPARATOR + srcY + SEPARATOR +
                       dstW + SEPARATOR + dstH + SEPARATOR + dstX + SEPARATOR + dstY + SEPARATOR +
                       flipedStr + SEPARATOR + END_SERIALIZATION_SIMBOL;

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

    return "1_" + serializedAction+ "_" + to_string(id) + "_x";;
}