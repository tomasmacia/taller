//
// Created by Tomás Macía on 03/09/2019.
//

#ifndef GAME_XMLPARSER_H
#define GAME_XMLPARSER_H

#include <string>
#include <vector>
#include "config/config.h"
#include "../credentials/Credentials.h"
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

class XMLParser {
public:
    Config* parse(string);

    Credentials* parseCredentials(string);
private:
    static constexpr const char* const DEFAULT_CONFIG_PATH = "configs/default.xml";
    static constexpr const char* const DEFAULT_CREDENTIALS_PATH = "configs/credentials-default.xml";

    XMLError loadFile(XMLDocument *document, string path, string defaultPath, string type);

    static XMLElement* getXMLElementSafe(XMLElement *element, vector<string> names);

    template <typename T>
    static T getSafeValueFromElement(XMLElement *element, vector<string> names, T (*func)(const char*), string section);

    Config* mapXMLDocumentToConfig(XMLDocument *doc, XMLDocument *docDefault);

    string getLoggerLevel(XMLElement *config);

    int wrapperServerModule(XMLElement *config, XMLElement *defaultConfig);

    int getServerMaxPlayers(XMLElement *config);

    Bindings getBindings(XMLElement *config);

    ScreenResolution wrapperScreenResolutionModule(XMLElement *config, XMLElement *defaultConfig);

    ScreenResolution getScreenResolution(XMLElement *config);

    Gameplay getGameplaySettings(XMLElement *config, XMLElement *defaultConfig);

    vector<Level> getGameplayLevels(XMLElement *gameplay);

    vector<CharacterXML> getGameplayCharacters(XMLElement *gameplay);

    vector<NPC> getGameplayNPCS(XMLElement *gameplay);

    Weapons getGameplayWeapons(XMLElement *gameplay);

    WeaponConfig getGameplayWeapon(XMLElement *weaponElement);

    Utilities getGameplayUtilities(XMLElement *gameplay);

    UtilityConfig getGameplayUtility(XMLElement *utility);

    template <typename T>
    static vector<T> mapSettingToVector(XMLElement *genericElement, string childNameType, T (*function)(XMLElement*, string), string section);

    static CharacterXML mapCharacter(XMLElement *characters, string currentChildName);

    static Level mapLevel(XMLElement *levels, string currentChildName);

    static NPC mapNPC(XMLElement *npcs, string currentChildName);

    static string charArrayToString(const char *c);

    string wrapperLoggerModule(XMLElement *config, XMLElement *defaultConfig);

    Bindings wrapperBindingsModule(XMLElement *config, XMLElement *defaultConfig);

    Sounds wrapperSoundsModule(XMLElement *config, XMLElement *defaultConfig);

    Gameplay wrapperGameplayModule(XMLElement *config, XMLElement *defaultConfig);

    vector<Level> wrapperGameplayLevelsModule(XMLElement *gameplay, XMLElement *defaultGameplay);

    vector<CharacterXML> wrapperGameplayCharactersModule(XMLElement *gameplay, XMLElement *defaultGameplay);

    vector<NPC> wrapperGameplayNPCSModule(XMLElement *gameplay, XMLElement *defaultGameplay);

    Weapons wrapperGameplayWeaponsModule(XMLElement *gameplay, XMLElement *defaultGameplay);

    Utilities wrapperGameplayUtilitiesModule(XMLElement *gameplay, XMLElement *defaultGameplay);

    static string dummyStringMap(XMLElement *genericElement, const string currentChildName);

    string getErrorMessageFromFile(string pathToFile, int lineNumber);

    static string getPathToElement(XMLElement *genericElement, vector<string> names, string section);

    // CREDENTIALS
    Credentials* mapXMLDocumentToCredentials(XMLDocument *doc, XMLDocument *docDefault);

    vector<UserCredentials> wrapperUsersModule(XMLElement *credentials, XMLElement *defaultCredentials);

    vector<UserCredentials> getUserCredentials(XMLElement *credentials);

    Sounds getSounds(XMLElement *config);
};

#endif //GAME_XMLPARSER_H