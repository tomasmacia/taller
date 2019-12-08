#include "xmlparser.h"
#include "config/config.h"
#include "config/characterxml.h"
#include "../logger/LogManager.h"
#include <tinyxml2.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
using namespace tinyxml2;


Config* XMLParser::parse(string pathToConfig) {
    LogManager::logInfo("[XML]: " + pathToConfig + "is the path to the config file.");
    XMLDocument doc;
    loadFile(&doc, pathToConfig, DEFAULT_CONFIG_PATH, "config");

    XMLDocument docDefault;
    loadFile(&docDefault, DEFAULT_CONFIG_PATH, DEFAULT_CONFIG_PATH, "config");

    Config* config = nullptr;

    try {
        config = mapXMLDocumentToConfig(&doc, &docDefault);
    } catch(string& msg) {
        LogManager::logError("[XML]: There was an error loading default config --> " + msg);
    }

    return config;
}

XMLError XMLParser::loadFile(XMLDocument *doc, string path, string defaultPath, string type) {
    vector<char> chars(path.c_str(), path.c_str() + path.size() + 1);
    XMLError eResult = doc->LoadFile(&chars[0]);


    if (eResult != XML_SUCCESS) {
        int specifiedDocErrorLineNumber = doc->ErrorLineNum();

        XMLError defaultResult = doc->LoadFile(defaultPath.c_str());

        if (defaultResult != XML_SUCCESS) { // TODO what should we do here?
            LogManager::logError("[XML]: Default " + type + " file located in " + defaultPath + " could not be loaded");
            return defaultResult;
        }

        if (path.empty()) {
            LogManager::logError("[XML]: Default " + type + " file not specified, using default " + type + " located in " + defaultPath);
        } else {
            LogManager::logError("[XML]: " + getErrorMessageFromFile(path, specifiedDocErrorLineNumber));
            LogManager::logError("[XML]: " + type + " file specified located in " + path +
            " could not be loaded. Using default " + type + " located in " + defaultPath);
        }
    }

    return eResult;
}

Config* XMLParser::mapXMLDocumentToConfig(XMLDocument *doc, XMLDocument *docDefault) {
    XMLElement *configElement = nullptr;
    XMLElement *defaultConfigElement = nullptr;
    if (doc == nullptr && docDefault == nullptr) {
        throw string("Error reading XML"); // to be catched in XMLParser::parse try-catch
    }

    if (doc != nullptr) {
        configElement = doc->FirstChildElement("config");
    }

    if (docDefault != nullptr) {
        defaultConfigElement = docDefault->FirstChildElement("config");
    }

    if (configElement == nullptr) {
        LogManager::logError("[XML]: Error reading config from XML. Using default config");
        configElement = defaultConfigElement; // do not try to create modules later from null, use default directly
    }

    auto* config = new Config();

    config->loggerLevel = wrapperLoggerModule(configElement, defaultConfigElement);
    config->bindings = wrapperBindingsModule(configElement, defaultConfigElement);
    config->sounds = wrapperSoundsModule(configElement, defaultConfigElement);
    config->screenResolution = wrapperScreenResolutionModule(configElement, defaultConfigElement);
    config->serverMaxPlayers = wrapperServerModule(configElement, defaultConfigElement);
    config->gameplay = wrapperGameplayModule(configElement, defaultConfigElement);


    return config;
}

string XMLParser::wrapperLoggerModule(XMLElement *config, XMLElement *defaultConfig) {
    string loggerLevel;
    try {
        loggerLevel = getLoggerLevel(config);
    } catch(string& msg) {
        LogManager::logError(msg);
        loggerLevel = getLoggerLevel(defaultConfig);
    }

    return loggerLevel;
}

string XMLParser::getLoggerLevel(XMLElement *config) {
    return getSafeValueFromElement(config, {"logger", "level"}, charArrayToString, "logger");
}

int XMLParser::wrapperServerModule(XMLElement *config, XMLElement *defaultConfig) {
    int serverMaxPlayers;
    try {
        serverMaxPlayers = getServerMaxPlayers(config);
    } catch(string& msg) {
        LogManager::logError(msg);
        serverMaxPlayers = getServerMaxPlayers(defaultConfig);
    }

    return serverMaxPlayers;
}

int XMLParser::getServerMaxPlayers(XMLElement *config) {
    return getSafeValueFromElement(config, {"server", "players"}, atoi, "server");
}

Bindings XMLParser::wrapperBindingsModule(XMLElement *config, XMLElement *defaultConfig) {
    Bindings bindings;
    try {
        bindings = getBindings(config);
    } catch (string& msg) {
        LogManager::logError(msg);
        bindings = getBindings(defaultConfig);
    }

    return bindings;
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

    bindings.KICK = getSafeValueFromElement(bindingsElement, {"kick"}, charArrayToString, section);
    bindings.JUMPKICK = getSafeValueFromElement(bindingsElement, {"jumpkick"}, charArrayToString, section);

    bindings.MUTE = getSafeValueFromElement(bindingsElement, {"mute"}, charArrayToString, section);

    return bindings;
}

Sounds XMLParser::wrapperSoundsModule(XMLElement *config, XMLElement *defaultConfig) {
    Sounds sounds;
    try {
        sounds = getSounds(config);
    } catch (string& msg) {
        LogManager::logError(msg);
        sounds = getSounds(defaultConfig);
    }

    return sounds;
}

Sounds XMLParser::getSounds(XMLElement *config) {
    XMLElement *soundsElement = getXMLElementSafe(config, {"sounds"});
    string section = "sounds";
    Sounds sounds;

    Boss boss;
    boss.death = getSafeValueFromElement(soundsElement, {"boss", "death"}, charArrayToString, section);

    Music music;
    music.soundtrack = getSafeValueFromElement(soundsElement, {"music", "soundtrack"}, charArrayToString, section);

    NpcSound npcSound;
    npcSound.death = getSafeValueFromElement(soundsElement, {"npc", "death"}, charArrayToString, section);
    npcSound.hit = getSafeValueFromElement(soundsElement, {"npc", "hit"}, charArrayToString, section);

    PlayerSound playerSound;
    playerSound.death = getSafeValueFromElement(soundsElement, {"player", "death"}, charArrayToString, section);
    playerSound.great = getSafeValueFromElement(soundsElement, {"player", "great"}, charArrayToString, section);
    playerSound.hit = getSafeValueFromElement(soundsElement, {"player", "hit"}, charArrayToString, section);
    playerSound.knifeHit = getSafeValueFromElement(soundsElement, {"player", "knifehit"}, charArrayToString, section);
    playerSound.pipeHit = getSafeValueFromElement(soundsElement, {"player", "pipehit"}, charArrayToString, section);

    UtilitySound utilitySound;
    utilitySound.barrelBreak = getSafeValueFromElement(soundsElement, {"utility", "barrelbreak"}, charArrayToString, section);
    utilitySound.boxBreak = getSafeValueFromElement(soundsElement, {"utility", "boxbreak"}, charArrayToString, section);

    sounds.boss = boss;
    sounds.music = music;
    sounds.npcs = npcSound;
    sounds.players = playerSound;
    sounds.utilities = utilitySound;

    return sounds;
}

ScreenResolution XMLParser::wrapperScreenResolutionModule(XMLElement *config, XMLElement *defaultConfig) {
    ScreenResolution screenResolution;
    try {
        screenResolution = getScreenResolution(config);
    } catch (string& msg) {
        LogManager::logError(msg);
        screenResolution = getScreenResolution(defaultConfig);
    }

    return screenResolution;
}

ScreenResolution XMLParser::getScreenResolution(XMLElement *config) {
    string section = "screen";
    XMLElement *screenResolutionElement = getXMLElementSafe(config, {section});
    ScreenResolution screenResolution;

    screenResolution.width = getSafeValueFromElement(screenResolutionElement, {"width"}, atoi, section);
    screenResolution.height = getSafeValueFromElement(screenResolutionElement, {"height"}, atoi, section);

    return screenResolution;
}

Gameplay XMLParser::wrapperGameplayModule(XMLElement *config, XMLElement *defaultConfig) {
    Gameplay gameplay = getGameplaySettings(config, defaultConfig);

    return gameplay;
}

Gameplay XMLParser::getGameplaySettings(XMLElement *config, XMLElement *defaultConfig) {
    XMLElement *gameplayElement = getXMLElementSafe(config, {"gameplay"});
    XMLElement *gameplayDefaultElement = getXMLElementSafe(defaultConfig, {"gameplay"});
    Gameplay gameplay;

    gameplay.levels = wrapperGameplayLevelsModule(gameplayElement, gameplayDefaultElement);
    gameplay.characters = wrapperGameplayCharactersModule(gameplayElement, gameplayDefaultElement);
    gameplay.npcs = wrapperGameplayNPCSModule(gameplayElement, gameplayDefaultElement);
    gameplay.weapons = wrapperGameplayWeaponsModule(gameplayElement, gameplayDefaultElement);
    gameplay.utilities = wrapperGameplayUtilitiesModule(gameplayElement, gameplayDefaultElement);

    return gameplay;
}

vector<Level> XMLParser::wrapperGameplayLevelsModule(XMLElement *gameplay, XMLElement *defaultGameplay) {
    vector<Level> levels;
    try {
        levels = getGameplayLevels(gameplay);
    } catch (string& msg) {
        LogManager::logError(msg);
        levels = getGameplayLevels(defaultGameplay);
    }

    return levels;
}

vector<Level> XMLParser::getGameplayLevels(XMLElement *gameplay) {
    string section = "levels";
    XMLElement *levelsElement = getXMLElementSafe(gameplay, {section});

    return mapSettingToVector(levelsElement, "level", XMLParser::mapLevel, section);
}

vector<CharacterXML> XMLParser::wrapperGameplayCharactersModule(XMLElement *gameplay, XMLElement *defaultGameplay) {
    vector<CharacterXML> characters;
    try {
        characters = getGameplayCharacters(gameplay);
    } catch (string& msg) {
        LogManager::logError(msg);
        characters = getGameplayCharacters(defaultGameplay);
    }

    return characters;
}

vector<CharacterXML> XMLParser::getGameplayCharacters(XMLElement *gameplay) {
    string section = "characters";
    XMLElement *charactersElement = getXMLElementSafe(gameplay, {section});

    return mapSettingToVector(charactersElement, "character", XMLParser::mapCharacter, section);
}

vector<NPC> XMLParser::wrapperGameplayNPCSModule(XMLElement *gameplay, XMLElement *defaultGameplay) {
    vector<NPC> npcs;
    try {
        npcs = getGameplayNPCS(gameplay);
    } catch (string& msg) {
        LogManager::logError(msg);
        npcs = getGameplayNPCS(defaultGameplay);
    }

    return npcs;
}

vector<NPC> XMLParser::getGameplayNPCS(XMLElement *gameplay) {
    string section = "enemies";
    XMLElement *npcsElement = getXMLElementSafe(gameplay, {section});

    return mapSettingToVector(npcsElement, "npc", XMLParser::mapNPC, section);
}

CharacterXML XMLParser::mapCharacter(XMLElement *characters, const string currentChildName) {
    CharacterXML character;
    character.name = getSafeValueFromElement(characters, {currentChildName.c_str(), "name"}, charArrayToString, "characters");
    character.stand = getSafeValueFromElement(characters, {currentChildName.c_str(), "standSprite"}, charArrayToString, "characters");
    character.walk = getSafeValueFromElement(characters, {currentChildName.c_str(), "walk"}, charArrayToString, "characters");
    character.jump = getSafeValueFromElement(characters, {currentChildName.c_str(), "jump"}, charArrayToString, "characters");
    character.punch = getSafeValueFromElement(characters, {currentChildName.c_str(), "punch"}, charArrayToString, "characters");
    character.crouch = getSafeValueFromElement(characters, {currentChildName.c_str(), "crouch"}, charArrayToString, "characters");
    character.kick = getSafeValueFromElement(characters, {currentChildName.c_str(), "kick"}, charArrayToString, "characters");
    character.jumpkick = getSafeValueFromElement(characters, {currentChildName.c_str(), "jumpkick"}, charArrayToString, "characters");
    character.disconnected = getSafeValueFromElement(characters, {currentChildName.c_str(), "disconnected"}, charArrayToString, "characters");

    return character;
}

Level XMLParser::mapLevel(XMLElement *levels, const string currentChildName) {
    Level level;

    XMLElement *levelI = getXMLElementSafe(levels, {currentChildName.c_str()});
    XMLElement *floorElement = getXMLElementSafe(levelI, {"floor"});
    XMLElement *farElement = getXMLElementSafe(levelI, {"far"});
    XMLElement *overlayElement = getXMLElementSafe(levelI, {"overlay"});
    XMLElement *middleElement = getXMLElementSafe(levelI, {"middle"});

    level.name = getSafeValueFromElement(levelI, {"name"}, charArrayToString, "levels");
    level.floor = mapSettingToVector(floorElement, "floor", dummyStringMap, "levels");
    level.far = mapSettingToVector(farElement, "far", dummyStringMap, "levels");
    level.overlay = mapSettingToVector(overlayElement, "overlay", dummyStringMap, "levels");

    if (middleElement != nullptr) { // not necessary in config
        level.middle = mapSettingToVector(middleElement, "middle", dummyStringMap, "levels");
    }

    return level;
}

string XMLParser::dummyStringMap(XMLElement *genericElement, const string currentChildName) {
    return getSafeValueFromElement(genericElement, {currentChildName.c_str()}, charArrayToString, "levels");
}

NPC XMLParser::mapNPC(XMLElement *npcs, const string currentChildName) {
    NPC npc;
    npc.difficulty = getSafeValueFromElement(npcs, {currentChildName.c_str(), "difficulty"}, charArrayToString, "enemies");
    npc.walk = getSafeValueFromElement(npcs, {currentChildName.c_str(), "walk"}, charArrayToString, "enemies");

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

Weapons XMLParser::wrapperGameplayWeaponsModule(XMLElement *gameplay, XMLElement *defaultGameplay) {
    Weapons weapons;
    try {
        weapons = getGameplayWeapons(gameplay);
    } catch (string& msg) {
        LogManager::logError(msg);
        weapons = getGameplayWeapons(defaultGameplay);
    }

    return weapons;
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

Utilities XMLParser::wrapperGameplayUtilitiesModule(XMLElement *gameplay, XMLElement *defaultGameplay) {
    Utilities utilities;
    try {
        utilities = getGameplayUtilities(gameplay);
    } catch (string& msg) {
        LogManager::logError(msg);
        utilities = getGameplayUtilities(defaultGameplay);
    }

    return utilities;
}

WeaponConfig XMLParser::getGameplayWeapon(XMLElement *weaponElement) {
    WeaponConfig weapon;
    weapon.amount = getSafeValueFromElement(weaponElement, {"amount"}, atoi, "weapons");
    weapon.sprite = getSafeValueFromElement(weaponElement, {"sprite"}, charArrayToString, "weapons");
    weapon.damage = getSafeValueFromElement(weaponElement, {"damage"}, atoi, "weapons");

    return weapon;
}

Utilities XMLParser::getGameplayUtilities(XMLElement *gameplay) {
    XMLElement *utilitiesElement = getXMLElementSafe(gameplay, {"utilities"});
    XMLElement *barrelsElement = getXMLElementSafe(utilitiesElement, {"barrel"});
    XMLElement *boxesElement = getXMLElementSafe(utilitiesElement, {"box"});

    Utilities utilities;

    utilities.barrel = getGameplayUtility(barrelsElement);
    utilities.box = getGameplayUtility(boxesElement);

    return utilities;
}

UtilityConfig XMLParser::getGameplayUtility(XMLElement *utilityElement) {
    UtilityConfig utility;
    utility.amount = getSafeValueFromElement(utilityElement, {"amount"}, atoi, "utilities");
    utility.standSprite = getSafeValueFromElement(utilityElement, {"sprite"}, charArrayToString, "utilities");
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
        throw string("El modulo " + section + " no se pudo parsear. " + getPathToElement(element, names, section) + " no existe y es obligatorio. Usando el archivo de configuración por defecto para este módulo");
    }

    return func(stringValue);
}


string XMLParser::getErrorMessageFromFile(string pathToFile, int lineNumber) {
    string configLine, errorMsg;
    ifstream read;

    read.open(pathToFile);

    int lineRead = 0;
    while (lineRead != lineNumber && getline(read, configLine)) {
        ++lineRead;
    }

    // if file contains fewer than lineNumber lines, getline in while conditions returns false
    if (lineRead == lineNumber) {
        errorMsg = "La línea " + to_string(lineNumber) + " no cumple con la sintaxis de XML --> " +  configLine;
    } else {
        errorMsg = "El archivo de configuración no cumple con la sintaxis XML";
    }

    read.close();

    return errorMsg;
}

string XMLParser::getPathToElement(XMLElement *genericElement, vector<string> names, string section) {
    string pathToElement;
    if (genericElement != nullptr) {
        pathToElement = genericElement->Name();
    } else {
        return "config->" + section;
    }


    for (auto &name : names) {
        pathToElement += "->" + name;
    }

    return pathToElement;
}


// ***********************************************
// ************** CREDENTIALS PARSE **************
// ***********************************************
Credentials *XMLParser::parseCredentials(string pathToCredentials) {

    LogManager::logInfo("[XML]: " + pathToCredentials +  " is the path to the credentials file.");
    XMLDocument doc;
    loadFile(&doc, pathToCredentials, DEFAULT_CREDENTIALS_PATH, "credentials");

    XMLDocument docDefault;
    loadFile(&docDefault, DEFAULT_CREDENTIALS_PATH, DEFAULT_CREDENTIALS_PATH, "credentials");

    Credentials* credentials = nullptr;

    try {
        credentials = mapXMLDocumentToCredentials(&doc, &docDefault);
    } catch(string& msg) {
        LogManager::logError("[XML]: There was an error loading default credentials --> " + msg);
    }

    return credentials;
}

Credentials* XMLParser::mapXMLDocumentToCredentials(XMLDocument *doc, XMLDocument *docDefault) {
    XMLElement *credentialsElement = nullptr;
    XMLElement *defaultCredentialsElement = nullptr;
    if (doc == nullptr && docDefault == nullptr) {
        throw string("Error reading XML"); // to be catched in XMLParser::parse try-catch
    }

    if (doc != nullptr) {
        credentialsElement = doc->FirstChildElement("credentials");
    }

    if (docDefault != nullptr) {
        defaultCredentialsElement = docDefault->FirstChildElement("credentials");
    }

    if (credentialsElement == nullptr) {
        LogManager::logError("[XML]: Error reading credentials from XML. Using default credentials");
        credentialsElement = defaultCredentialsElement; // do not try to create modules later from null, use default directly
    }

    auto* credentials = new Credentials();

    credentials->users = wrapperUsersModule(credentialsElement, defaultCredentialsElement);


    return credentials;
}

vector<UserCredentials> XMLParser::wrapperUsersModule(XMLElement *credentials, XMLElement *defaultCredentials) {
    vector<UserCredentials> users;
    try {
        users = getUserCredentials(credentials);
    } catch (string& msg) {
        LogManager::logError(msg);
        users = getUserCredentials(defaultCredentials);
    }

    return users;
}

vector<UserCredentials> XMLParser::getUserCredentials(XMLElement *credentials) {
    vector<UserCredentials> users;
    XMLElement *user = nullptr;

    if (credentials != nullptr) {
        user = credentials->FirstChildElement("user");
    }

    while(user != nullptr) {
        UserCredentials userCredentials;

        userCredentials.username = getSafeValueFromElement(user, {"username"}, charArrayToString, "user");
        userCredentials.password = getSafeValueFromElement(user, {"password"}, charArrayToString, "user");

        users.push_back(userCredentials);

        user = user->NextSiblingElement("user");
    }

    return users;
}
