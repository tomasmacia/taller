#ifndef GAME_GAMECLIENT_H_
#define GAME_GAMECLIENT_H_

class GameClient {
public:
    // *************************
    // ******* SINGLETON *******
    // *************************

    static GameClient &getInstance() {
        static GameClient instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    GameClient(GameClient const &) = delete;
    void operator=(GameClient const &) = delete;



    void start();

private:
    GameClient() {}

};

#endif //GAME_GAMECLIENT_H_
