#include "GameServer.h"
#include "Controller.h"
#include "LevelBuilder.h"

#include <iostream>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("[GAME]: Se inicia Game");

    initController();
    startServer();          //1 thread de listen de conexiones nuevas y 4 threads por cliente nuevo

    initWaitingScreen();
    waitUnitAllPlayersConnected();

    initGameModel();
    gameLoop();

    closeServer();          //se cierra el thread se server y (previamente se cierran los 4 threads child)

    LogManager::logInfo("[GAME]: Juego terminado");
    LogManager::logInfo("=======================================");

    cout << "everything endded up nicely :D" << endl;
}

//GAME LOOP
//=========================================================================================

void GameServer::gameLoop(){

    while (isOn() && levelBuilder->hasNextLevel() && notAllPlayersDisconnected()) {

        levelBuilder->loadNext();
        LogManager::logInfo("=======================================");
        LogManager::logInfo("[GAME]: se inicia game loop de este nivel");

        while (isOn() && !levelBuilder->levelFinished() && notAllPlayersDisconnected()) {
            update();
            sendUpdate();
            usleep(SLEEP_TIME);
        }
         if (notAllPlayersDisconnected()) {
            ScoreScreen();
            controller->sendUpdate(scoreContainer,server);
            SDL_Delay(4000);
            cleanScreens();
        }

        LogManager::logInfo("[GAME]: Nivel terminado");
        LogManager::logInfo("=======================================");
    }
    if (notAllPlayersDisconnected() ) {
        finalScreen();
        controller->sendUpdate(scoreContainer,server);
        SDL_Delay(4000);
        cleanScreens();//
    } 
    on = false;
    server->stopListening();
}

void GameServer::update() {
    entityManager->update();
    controller->clearAllInputs();
}

void GameServer::sendUpdate() {
    //auto* sendables = sceneDirector->generateSendables();
    auto* sendables = entityManager->generateSendables();

    /*
    for (auto sendable : *sendables){
        if (sendable->_soundable != nullptr){
            cout<<"Se mando a emitir: "<<sendable->_soundable->getPath()<<" ,cant total paquetes a enviar: "<<sendables->size()<<endl;
        }
    }*/

    controller->sendUpdate(sendables, server);
}

//API
//=========================================================================================

std::string GameServer::validateLogin(const std::string& user,const std::string& pass, int userId){


    if (credentialsAreValid(user,pass)){
        if (userAlreadyLoggedIn(user)){
            if (userIsDisconnected(user)){
                return processReconectionAndEmitSuccesMessage(user,userId);
            }
            else{
                return controller->getAlreadyLoggedInMessage();
            }
        }
        else{
            if (serverFull()){
                return controller->getServerFullMessage();
            }
            else{
                return processConectionAndEmitSuccesMessage(user, pass, userId);
            }
        }
    }
    else{
        return controller->getInvalidCredentialMessage();
    }
}

void GameServer::addNewIDToGame(int id) {
    IDManager::getInstance().addNewIdPlayer(id);
}

void GameServer::reemplazePreviousIDWith(int oldID, int newID) {
    IDManager::getInstance().reemplaze(oldID, newID);
}

int GameServer::getCurrentLevelWidth(){
    return levelBuilder->getCurrentLevelWidth();
}

void GameServer::reciveNewInput(tuple<Action,int> input){
    return controller->setInput(input);
}

bool GameServer::isActive(){
    return hasInstance;
}

bool GameServer::playersCanMove(){
    return loggedPlayersPassByUser.size() == maxPlayers;
}

bool GameServer::isIDLogged(int ID){
    return loggedPlayersUserByID.count( ID );
}

void GameServer::sendWaitingScreen() {
    controller->sendUpdate(waitingScreenContainer,server);
}

//SERVER RELATED
//=========================================================================================
void GameServer::startServer(){
    server = new Server(this);
    server->init();
    listenConnectionsThread = std::thread(&Server::listenThread,server);
    LogManager::logInfo("[INIT]: Server inicializado");
}

void GameServer::closeServer(){
    listenConnectionsThread.join();
    server->close();
}

void GameServer::waitUnitAllPlayersConnected(){

    while ((loggedPlayersPassByUser.size() != maxPlayers) ||
            (!disconectedPlayers.empty())){
        sendWaitingScreen();
        usleep(SLEEP_TIME);
    }
}

bool GameServer::notAllPlayersDisconnected(){
    return disconectedPlayers.size() < maxPlayers;
}

void GameServer::connectionLostWith(int id){

    if (loggedPlayersUserByID.count(id)){

        string name = loggedPlayersUserByID.at(id).name;
        disconectedPlayers.insert({name,id});
    }
    if (entityManager != nullptr){
        entityManager->disconectPlayerByID(id);
    }
}



void GameServer::cleanScreens(){
    if (!scoreContainer->empty()){
        delete(scoreContainer->front());
    }
    scoreContainer->pop_front();
    scoreContainer = nullptr;
    scoreScreenRenderable = nullptr;
}


void GameServer::finalScreen(){


/*     scoreContainer = nullptr;
    delete(scoreScreenRenderable);
    scoreScreenRenderable = nullptr; */

    string path = "resources/sprites/screens/complete.png";

    ImageSize imageSize = ImageUtils::getImageSize(path);
    int imageWidth = imageSize.width;
    int imageHeight = imageSize.height;

    int screenWidth = config->screenResolution.width;
    int screenHeight = config->screenResolution.height;

    Rect src = {0,0,imageWidth,imageHeight};
    Rect dst = {0,0,screenWidth,screenHeight};

    scoreScreenRenderable = new Sendable(new Renderable(path, src, dst, false), nullptr);
    scoreContainer = new list<Sendable*>();
    scoreContainer->push_back(scoreScreenRenderable);
}


void GameServer::ScoreScreen(){

/*     scoreContainer = nullptr;
    delete(scoreScreenRenderable);
    scoreScreenRenderable = nullptr; */


    string path = "resources/sprites/screens/mid.png";

    ImageSize imageSize = ImageUtils::getImageSize(path);
    int imageWidth = imageSize.width;
    int imageHeight = imageSize.height;

    int screenWidth = config->screenResolution.width;
    int screenHeight = config->screenResolution.height;

    Rect src = {0,0,imageWidth,imageHeight};
    Rect dst = {0,0,screenWidth,screenHeight};

    scoreScreenRenderable = new Sendable(new Renderable(path, src, dst, false), nullptr);
    scoreContainer = new list<Sendable*>();
    scoreContainer->push_back(scoreScreenRenderable);
    int y= (screenHeight/2);
    auto players = entityManager->getPlayers();
    for (auto a:players){
        CharacterName( y, a->getID(),scoreContainer);
        renderPuntaje(a->getScore(),screenWidth-50,y,scoreContainer);
            
        y+=50; 
    }

}


void GameServer::CharacterName(int y, int id,list<Sendable*>* wa){
    string path1;
    ImageSize imageSize1;
    std::map<int,User>::iterator it;
    it = loggedPlayersUserByID.find(id);
    auto user = it->second.name;
 //   std::cerr << user<< std::endl;
    if (user.compare("FRAN") == 0){
        path1="resources/sprites/score/fran.png";
    }
    if (user.compare("CRIS") == 0){
        path1="resources/sprites/score/cris.png";
    }
    if (user.compare("AXEL") == 0){
        path1="resources/sprites/score/axel.png";
    }
    if (user.compare("TOMI") == 0) {
        path1="resources/sprites/score/tomi.png";
    }
    imageSize1 = ImageUtils::getImageSize(path1);
    int imageWidth1 = imageSize1.width;
    int imageHeight1 = imageSize1.height;

    Rect src1 = {0,0,imageWidth1,imageHeight1};
    Rect dst1 = {50,y,imageWidth1 * 2,imageHeight1 * 2};

    Sendable* c = new Sendable(new Renderable(path1, src1, dst1, false), nullptr);
    wa->push_back(c);
}


void GameServer::renderPuntaje(int score,int x, int y,list<Sendable*>* wa){
    int score_ = score;
    bool asd =true;
    string path1;
    int x_ = x, y_= y;
    if (score != NULL ) {

        while(asd)
        {
            
            Sendable* c = nullptr;
            ImageSize imageSize1;
            int resto = score_ % 10;


            if (resto == 0){
                 path1 = "resources/sprites/score/zero.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
   //             std::cerr << "0"<< std::endl;
            }
            else if (resto == 1)
            {
                path1 = "resources/sprites/score/one.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
    //            std::cerr << "1"<< std::endl;
            }
            else if (resto == 2)
            {
                path1 = "resources/sprites/score/two.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
    //            std::cerr << "2"<< std::endl;
            }
            else if (resto == 3)
            {
                 path1 = "resources/sprites/score/three.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
     //           std::cerr << "3"<< std::endl;
            }
            else if (resto == 4)
            {
                 path1 = "resources/sprites/score/four.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
     //           std::cerr << "4"<< std::endl;
            }
            else if (resto == 5)
            {
                path1 = "resources/sprites/score/five.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
       //         std::cerr << "5"<< std::endl;
            }
            else if (resto == 6)
            {
                path1 = "resources/sprites/score/six.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
    //            std::cerr << "6"<< std::endl;
            }
            else if (resto == 7)
            {
                path1 = "resources/sprites/score/seven.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
      //          std::cerr << "7"<< std::endl;
            }
            else if (resto == 8)
            {
                 path1 = "resources/sprites/score/eigth.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
      //          std::cerr << "8"<< std::endl;
            }
            else if (resto == 9)
            {
                 path1 = "resources/sprites/score/nine.png";

                ImageSize imageSize1 = ImageUtils::getImageSize(path1);
      //          std::cerr << "9"<< std::endl;
            }
            int imageWidth1 = imageSize1.width;
            int imageHeight1 = imageSize1.height;

            int screenWidth1 = 32;
            int screenHeight1 = 32;
            x_ -= screenHeight1;

            Rect src1 = {0,0,imageWidth1,imageHeight1};
            Rect dst1 = {x_,y_,screenWidth1,screenHeight1 };

            c= new Sendable(new Renderable(path1, src1, dst1, false), nullptr);
            wa->push_back(c);

            score_ -= resto;
            if (score_ <= 0){
                asd =false;
            }
            score_ = score_/10;

        }
    }

}


//CONTROLLER RELATED
//=========================================================================================

void GameServer::initController() {
    controller = new Controller(this);
    LogManager::logDebug("[INIT]: inicializado Controller");
}

//LOGIN RELATED
//=========================================================================================
bool GameServer::serverFull(){
    return loggedPlayersPassByUser.size() == maxPlayers;
}

bool GameServer::credentialsAreValid(const string& user, const string& pass){
    return validUser(user) && validPass(user,pass);
}

bool GameServer::userAlreadyLoggedIn(const string& user){
    return userInLoggedPlayers(user);
}

bool GameServer::userIsDisconnected(const string& user){
    return IDInDisconnectedPlayers(user);
}

bool GameServer::validUser(const string& user){
    return validCredentials.find(user) != validCredentials.end();
}

bool GameServer::validPass(const string& user, const string& pass){
    return validCredentials.at(user) == pass;
}

bool GameServer::userInLoggedPlayers(const string& user){
    return loggedPlayersPassByUser.find(user) != loggedPlayersPassByUser.end();
}

bool GameServer::IDInDisconnectedPlayers(const string& user){
    return disconectedPlayers.find(user) != disconectedPlayers.end();
}

string GameServer::processConectionAndEmitSuccesMessage(const string& name, const string& pass, int id){

    User user(name,this->getNewColor());


    loggedPlayersPassByUser.insert({ user.name, pass });
    loggedPlayersUserByID.insert({ id, user });
    loggedPlayersIDbyUser.insert({user.name,id});
    addNewIDToGame(id);
    server->client_noBlock(id);

    return controller->getSuccesfullLoginMessage(user.color, id);
}

string GameServer::processReconectionAndEmitSuccesMessage(const string& name, int newID){

    int oldID = loggedPlayersIDbyUser.at(name);
    User user = loggedPlayersUserByID.at(oldID);

    loggedPlayersUserByID.erase(oldID);
    loggedPlayersUserByID.insert({newID,user});

    loggedPlayersIDbyUser.at(user.name) = newID;

    reemplazePreviousIDWith(oldID, newID);

    disconectedPlayers.erase(user.name);
    if (entityManager != nullptr){
        entityManager->reconectPlayerByID(oldID, newID);
    }
    server->client_noBlock(newID);

    return controller->getSuccesfullLoginMessage(user.color,newID);
}

string GameServer::getNewColor() {
    switch (currentColor){
        case BLUE:
            currentColor = RED;
            return "BLUE";
        case RED:
            currentColor = GREEN;
            return "RED";
        case GREEN:
            currentColor = YELLOW;
            return "GREEN";
        case YELLOW:
            currentColor = COLOR_UNDEFINED;
            return "YELLOW";
        case COLOR_UNDEFINED:
            LogManager::logError("[LOGIN]: tried to assign undefined color");
            return "COLOR_UNDEFINED";
    }
}


//INIT
//=========================================================================================
void GameServer::initWaitingScreen() {
    string path = "resources/sprites/screens/waiting_for_your_teammates.png";

    ImageSize imageSize = ImageUtils::getImageSize(path);
    int imageWidth = imageSize.width;
    int imageHeight = imageSize.height;

    int screenWidth = config->screenResolution.width;
    int screenHeight = config->screenResolution.height;

    Rect src = {0,0,imageWidth,imageHeight};
    Rect dst = {0,0,screenWidth,screenHeight};

    waitingScreenSendable = new Sendable(new Renderable(path, src, dst, false), nullptr);
    waitingScreenContainer = new list<Sendable*>();
    waitingScreenContainer->push_back(waitingScreenSendable);
}

void GameServer::initGameModel() {
    entityManager = initLevelBuilder();
    LogManager::logDebug("[INIT]: inicializado EntityManager");
    LogManager::logDebug("[INIT]: inicializado LevelBuilder");
    LogManager::logInfo("[INIT]: Modelo inicializado");
}

void GameServer::init() {
    initConfig();
    loadValidCredenctials();
    maxPlayers = config->serverMaxPlayers;

    LogManager::logDebug("[INIT]: inicializado Config");
    LogManager::logDebug("[INIT]: cargado credenciales");
    LogManager::logDebug("=======================================");
}

void GameServer::loadValidCredenctials(){
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToUserCredentialsFileName();

    XMLParser xmlParser;
    Credentials *credentials = xmlParser.parseCredentials(pathToConfigFile);

    for (auto &userCredentials : credentials->users) {
        this->validCredentials.insert(std::make_pair(userCredentials.username, userCredentials.password));
    }
}

EntityManager* GameServer::initLevelBuilder() {
    this->levelBuilder = new LevelBuilder(controller, config);
    return levelBuilder->getEntityManager();
}

//DESTROY
//=========================================================================================

void GameServer::destroy() {
    if (!waitingScreenContainer->empty()){
        delete(waitingScreenContainer->front());
    }
    waitingScreenContainer->pop_front();
    waitingScreenContainer = nullptr;
    waitingScreenSendable = nullptr;
    delete(server);
    server = nullptr;
    delete(levelBuilder);
    levelBuilder = nullptr;
    baseClassFreeMemory();
    //LogManager::logDebug("Memoria de Game Server liberada");
}