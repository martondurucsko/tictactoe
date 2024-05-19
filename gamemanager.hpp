#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "button.hpp"
#include "dialog.hpp"

using namespace genv;

enum Players {
    X = 0,
    O = 1
};

enum GameModes {
    PvP = 0,
    PvA = 1,
    AvA = 2
};

class GameManager
{
public:
    GameManager(std::vector<Widget*>& w, int x,int y, int width, int height);
protected:
    std::vector<Widget*>& w;
    int x;
    int y;
    int width;
    int height;
    int amountToWin = 5;
    int cellNumber = 15;
    Dialog* menu;
    Button*** cells;
    Players currentPlayer = Players::X;
    GameModes currentGameMode = GameModes::PvP;
    virtual void createMenu();
    virtual void openMainMenu();
    virtual void reset();
    virtual void checkWinningConditions();
    virtual void createMap();
    virtual void handleWin(bool isDraw);
    virtual int minimax(int depth, bool isMax, int alpha, int beta, int maxDepth);
    virtual Position findBestMove();
    virtual int evaluate();
    virtual bool movesLeft();
    virtual void renderMap();
    virtual void startAILoop();
    virtual void makeAIMove();
};

#endif
