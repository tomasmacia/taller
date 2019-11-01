//
// Created by axel on 1/11/19.
//
#include <vector>
#include "ObjectSerializer.h"

using namespace std;

//API
//=========================================================================================
bool ObjectSerializer::validLoginIDFromServerMessage(vector<string> currentParsedMessage){
    return currentParsedMessage.size() != 3; //header,id,END_SERIALIZATION_SIMBOL
}
