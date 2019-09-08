#include "xmlparser.h"
#include "config/config.h"
#include <tinyxml2.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace tinyxml2;


Config XMLParser::parse(string pathToConfig) {
    cout << pathToConfig << " is the path to the config file." << endl;
    XMLDocument doc;
    loadFile(&doc, pathToConfig);

    Config config;

    try {
        config = mapXMLDocumentToConfig(&doc);
    } catch(string& msg) { // TODO: load specific modules if fail
        XMLDocument docDefault;
        loadFile(&docDefault, DEFAULT_CONFIG_PATH);
        config = mapXMLDocumentToConfig(&docDefault);
    }

    return config;
}

XMLError XMLParser::loadFile(XMLDocument *doc, string pathToConfig) {
    vector<char> chars(pathToConfig.c_str(), pathToConfig.c_str() + pathToConfig.size() + 1);
    XMLError eResult = doc->LoadFile(&chars[0]);

    if (eResult != XML_SUCCESS) {
        XMLError defaultResult = doc->LoadFile(DEFAULT_CONFIG_PATH);

        if (defaultResult != XML_SUCCESS) { // TODO what should we do here?
            cerr << "Default config file located in " << DEFAULT_CONFIG_PATH << " could not be loaded" << endl;
            return defaultResult;
        }

        if (pathToConfig.empty()) {
            cout << "Default config file not specified, using default config located in " << DEFAULT_CONFIG_PATH << endl;
        } else {
            cout << "Config file specified located in " << pathToConfig <<
            " could not be loaded. Using default config located in " << DEFAULT_CONFIG_PATH << endl;
        }
    }

    return eResult;
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
    return getSafeValueFromElement(config, {"logger", "level"}, charArrayToString, "logger");string(config->FirstChildElement("logger")->FirstChildElement("level")->GetText());
}

Bindings XMLParser::getBindings(XMLElement *config) {
    XMLElement *bindingsElement = getXMLElementSafe(config, {"bindings"});
    string section = "bindings";
    Bindings bindings;

    bindings.UP = getSafeValueFromElement(bindingsElement, {"up"}, charArrayToString, section);
    bindings.DOWN = getSafeValueFromElement(bindingsElement, {"down"}, charArrayToString, section);
    bindings.LEFT = getSafeValueFromElement(bindingsElement, {"left"}, charArrayToString, section);
    bindings.RIGHT = getSafeValueFromElement(bindingsElement, {"right"}, charArrayToString, section);

    bindings.JUMP = getSafeValueFromElement(bindingsElement, {"jump"}, charArrayToString, section);
    bindings.ATTACK = getSafeValueFromElement(bindingsElement, {"attack"}, charArrayToString, section);
    bindings.CROUCH = getSafeValueFromElement(bindingsElement, {"crouch"}, charArrayToString, section);

    return bindings;
}

Gameplay XMLParser::getGameplaySettings(XMLElement *config) {
    XMLElement *gameplayElement = config->FirstChildElement("gameplay");
    Gameplay gameplay;

    gameplay.levels = getGameplayLevels(gameplayElement);
    gameplay.characters = getGameplayCharacters(gameplayElement);
    gameplay.npcs = getGameplayNPCS(gameplayElement);
    gameplay.weapons = getGameplayWeapons(gameplayElement);
    gameplay.utilities = getGameplayUtilites(gameplayElement);

    return gameplay;
}

vector<Level> XMLParser::getGameplayLevels(XMLElement *gameplay) {
    string section = "levels";
    XMLElement *levelsElement = getXMLElementSafe(gameplay, {section});

    return mapSettingToVector(levelsElement, "level", XMLParser::mapLevel, section);
}

vector<Character> XMLParser::getGameplayCharacters(XMLElement *gameplay) {
    string section = "characters";
    XMLElement *charactersElement = getXMLElementSafe(gameplay, {section});

    return mapSettingToVector(charactersElement, "character", XMLParser::mapCharacter, section);
}

vector<NPC> XMLParser::getGameplayNPCS(XMLElement *gameplay) {
    string section = "npcs";
    XMLElement *npcsElement = getXMLElementSafe(gameplay, {section});

    return mapSettingToVector(npcsElement, "npc", XMLParser::mapNPC, section);
}

Character XMLParser::mapCharacter(XMLElement *characters, const string currentChildName) {
    Character character;
    character.name = getSafeValueFromElement(characters, {currentChildName.c_str(), "name"}, charArrayToString, "characters");

    return character;
}

Level XMLParser::mapLevel(XMLElement *levels, const string currentChildName) {
    Level level;

    return level;
}

NPC XMLParser::mapNPC(XMLElement *npcs, const string currentChildName) {
    NPC npc;
    npc.difficulty = getSafeValueFromElement(npcs, {currentChildName.c_str(), "difficulty"}, charArrayToString, "npcs");

    return npc;
}

template <typename T>
vector<T> XMLParser::mapSettingToVector(XMLElement *genericElement, const string childNameType, T (*function)(XMLElement*, string), string section) {
    int amount = getSafeValueFromElement(genericElement, {"amount"}, atoi, section);

    vector<T> vectorOfT;

    for (int i = 1; i <= amount; ++i) {
        string currentChildName = childNameType + to_string(i);
        T configEntity = function(genericElement, currentChildName);

        vectorOfT.push_back(configEntity);
    }

    return vectorOfT;
}

Weapons XMLParser::getGameplayWeapons(XMLElement *gameplay) {
    XMLElement *weaponsElement = getXMLElementSafe(gameplay, {"weapons"});
    XMLElement *knifeElement = getXMLElementSafe(weaponsElement, {"knife"});
    XMLElement *tubeElement = getXMLElementSafe(weaponsElement, {"tube"});
    Weapons weapons;

    weapons.knife = getGameplayWeapon(knifeElement);
    weapons.tube = getGameplayWeapon(tubeElement);

    return weapons;
}

Weapon XMLParser::getGameplayWeapon(XMLElement *weaponElement) {
    Weapon weapon;
    weapon.amount = getSafeValueFromElement(weaponElement, {"amount"}, atoi, "weapons");
    weapon.damage = getSafeValueFromElement(weaponElement, {"damage"}, atoi, "weapons");

    return weapon;
}

Utilities XMLParser::getGameplayUtilites(XMLElement *gameplay) {
    XMLElement *utilitiesElement = getXMLElementSafe(gameplay, {"utilities"});
    XMLElement *barrelsElement = getXMLElementSafe(utilitiesElement, {"barrel"});
    XMLElement *boxesElement = getXMLElementSafe(utilitiesElement, {"box"});

    Utilities utilities;

    utilities.barrel = getGameplayUtility(barrelsElement);
    utilities.box = getGameplayUtility(boxesElement);

    return utilities;
}

Utility XMLParser::getGameplayUtility(XMLElement *utilityElement) {
    Utility utility;
    utility.amount = getSafeValueFromElement(utilityElement, {"amount"}, atoi, "utilities");
    utility.knivesDropProb = getSafeValueFromElement(utilityElement, {"contains", "knives"}, atof, "utilities");
    utility.tubesDropProb = getSafeValueFromElement(utilityElement, {"contains", "tubes"}, atof, "utilities");

    return utility;
}


string XMLParser::charArrayToString(const char* c) {
    return string(c);
}

XMLElement* XMLParser::getXMLElementSafe(XMLElement *element, vector<string> names) {
    if (element == nullptr) {
        return nullptr;
    }

    XMLElement *currentElement = element;

    for (auto name : names) {
        XMLElement *nextElement = currentElement->FirstChildElement(name.c_str());
        if (nextElement == nullptr) {
            return nullptr;
        }

        currentElement = nextElement;
    }

    return currentElement;
}


template <typename T>
T XMLParser::getSafeValueFromElement(XMLElement *element, vector<string> names, T (*func)(const char*), string section) {
    XMLElement *iterateElement = getXMLElementSafe(element, names);

    const char* stringValue = "";

    if (iterateElement != nullptr) {
        stringValue = iterateElement->GetText();
    } else {
        throw "Section " + section + " could not be parsed";
    }

    return func(stringValue);
}

