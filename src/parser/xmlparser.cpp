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

    return mapXMLDocumentToConfig(&doc);
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
    gameplay.weapons = getGameplayWeapons(gameplayElement);
    gameplay.utilities = getGameplayUtilites(gameplayElement);

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
    XMLElement *weaponsElement = gameplay->FirstChildElement("weapons");
    XMLElement *knifeElement = weaponsElement->FirstChildElement("knife");
    XMLElement *tubeElement = weaponsElement->FirstChildElement("tube");
    Weapons weapons;

    weapons.knife = getGameplayWeapon(knifeElement);
    weapons.tube = getGameplayWeapon(tubeElement);

    return weapons;
}

Weapon XMLParser::getGameplayWeapon(XMLElement *weaponElement) {
    Weapon weapon;
    weapon.amount = weaponElement->FirstChildElement("amount")->IntText();
    weapon.damage = weaponElement->FirstChildElement("damage")->IntText();

    return weapon;
}

Utilities XMLParser::getGameplayUtilites(XMLElement *gameplay) {
    XMLElement *utilitiesElement = gameplay->FirstChildElement("utilities");
    XMLElement *barrelsElement = utilitiesElement->FirstChildElement("barrel");
    XMLElement *boxesElement = utilitiesElement->FirstChildElement("box");

    Utilities utilities;

    utilities.barrel = getGameplayUtility(barrelsElement);
    utilities.box = getGameplayUtility(boxesElement);

    return utilities;
}

Utility XMLParser::getGameplayUtility(XMLElement *utilityElement) {
    Utility utility;
    utility.amount = utilityElement->FirstChildElement("amount")->IntText();
    utility.knivesDropProb = utilityElement->FirstChildElement("contains")->FirstChildElement("knives")->DoubleText();
    utility.tubesDropProb = utilityElement->FirstChildElement("contains")->FirstChildElement("tubes")->DoubleText();

    return utility;
}

