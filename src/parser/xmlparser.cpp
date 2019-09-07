#include "xmlparser.h"
#include "config/config.h"
#include <tinyxml2.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace tinyxml2;


Config XMLParser::parse(string pathToConfig) {
    cout << pathToConfig << " is the path to the config file." << "\n";
    XMLDocument doc;
    vector<char> chars(pathToConfig.c_str(), pathToConfig.c_str() + pathToConfig.size() + 1);
    doc.LoadFile(&chars[0]);

    return mapXMLDocumentToConfig(&doc);
}

Config XMLParser::mapXMLDocumentToConfig(XMLDocument *doc) {
    Config config;
    XMLElement *configElement = doc->FirstChildElement("config");

    config.loggerLevel = getLoggerLevel(configElement);
    config.bindings = getBindings(configElement);
    config.gameplay = getGameplaySettings(configElement);


    return config;
}

string XMLParser::getLoggerLevel(XMLElement *config) {
    return string(config->FirstChildElement("logger")->FirstChildElement("level")->GetText());
}

Bindings XMLParser::getBindings(XMLElement *config) {
    XMLElement *bindingsElement = config->FirstChildElement("bindings");
    Bindings bindings;

    bindings.UP = string(bindingsElement->FirstChildElement("up")->GetText());
    bindings.DOWN = string(bindingsElement->FirstChildElement("down")->GetText());
    bindings.LEFT = string(bindingsElement->FirstChildElement("left")->GetText());
    bindings.RIGHT = string(bindingsElement->FirstChildElement("right")->GetText());

    bindings.JUMP = string(bindingsElement->FirstChildElement("jump")->GetText());
    bindings.ATTACK = string(bindingsElement->FirstChildElement("attack")->GetText());
    bindings.CROUCH = string(bindingsElement->FirstChildElement("crouch")->GetText());

    return bindings;
}

Gameplay XMLParser::getGameplaySettings(XMLElement *config) {
    XMLElement *gameplayElement = config->FirstChildElement("gameplay");
    Gameplay gameplay;

    gameplay.levels = getGameplayLevels(gameplayElement);
    gameplay.characters = getGameplayCharacters(gameplayElement);
    gameplay.npcs = getGameplayNPCS(gameplayElement);
//    gameplay.weapons = getGameplayWeapons(gameplayElement);
//    gameplay.utilities = getGameplayUtilites(gameplayElement);

    return gameplay;
}

vector<Level> XMLParser::getGameplayLevels(XMLElement *gameplay) {
    XMLElement *levelsElement = gameplay->FirstChildElement("levels");

    return mapSettingToVector(levelsElement, "level", XMLParser::mapLevel);
}

vector<Character> XMLParser::getGameplayCharacters(XMLElement *gameplay) {
    XMLElement *charactersElement = gameplay->FirstChildElement("characters");

    return mapSettingToVector(charactersElement, "character", XMLParser::mapCharacter);
}

vector<NPC> XMLParser::getGameplayNPCS(XMLElement *gameplay) {
    XMLElement *npcsElement = gameplay->FirstChildElement("npcs");

    return mapSettingToVector(npcsElement, "npc", XMLParser::mapNPC);
}

Character XMLParser::mapCharacter(XMLElement *characters, const string currentChildName) {
    Character character;
    character.name = string(characters->FirstChildElement(currentChildName.c_str())->FirstChildElement("name")->GetText());

    return character;
}

Level XMLParser::mapLevel(XMLElement *levels, const string currentChildName) {
    Level level;
    // character.name = string(levels->FirstChildElement(currentChildName.c_str())->FirstChildElement("leve")->GetText());

    return level;
}

NPC XMLParser::mapNPC(XMLElement *npcs, const string currentChildName) {
    NPC npc;
    npc.difficulty = string(npcs->FirstChildElement(currentChildName.c_str())->FirstChildElement("difficulty")->GetText());

    return npc;
}

template <typename T>
vector<T> XMLParser::mapSettingToVector(XMLElement *genericElement, const string childNameType, T (*function)(XMLElement*, string)) {
    int amount = genericElement->FirstChildElement("amount")->IntText();

    vector<T> vectorOfT;

    for (int i = 1; i <= amount; ++i) {
        string currentChildName = childNameType + to_string(i);
        T configEntity = function(genericElement, currentChildName);

        vectorOfT.push_back(configEntity);
    }

    return vectorOfT;
}

Weapons XMLParser::getGameplayWeapons(XMLElement *gameplay) {

}

Utilities XMLParser::getGameplayUtilites(XMLElement *gameplay) {

}

