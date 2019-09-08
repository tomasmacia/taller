//
// Created by Tomás Macía on 03/09/2019.
//

#ifndef GAME_XMLPARSER_H
#define GAME_XMLPARSER_H

#include <string>
#include <vector>
#include "config/config.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class XMLParser {
public:
    Config parse(string);
private:
    static constexpr const char* const DEFAULT_CONFIG_PATH = "configs/default.xml";

    XMLError loadFile(XMLDocument *document, string pathToConfig);

    Config mapXMLDocumentToConfig(XMLDocument *doc);

    string getLoggerLevel(XMLElement *config);

    Bindings getBindings(XMLElement *config);

    Gameplay getGameplaySettings(XMLElement *config);

    vector<Level> getGameplayLevels(XMLElement *gameplay);

    vector<Character> getGameplayCharacters(XMLElement *gameplay);

    vector<NPC> getGameplayNPCS(XMLElement *gameplay);

    Weapons getGameplayWeapons(XMLElement *gameplay);

    Weapon getGameplayWeapon(XMLElement *weaponElement);

    Utilities getGameplayUtilites(XMLElement *gameplay);

    Utility getGameplayUtility(XMLElement *utility);

    template <typename T>
    vector<T> mapSettingToVector(XMLElement *genericElement, string childNameType, T (*function)(XMLElement*, string));

    static Character mapCharacter(XMLElement *characters, string currentChildName);

    static Level mapLevel(XMLElement *levels, string currentChildName);

    static NPC mapNPC(XMLElement *npcs, string currentChildName);
};

#endif //GAME_XMLPARSER_H