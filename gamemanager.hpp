#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "button.hpp"
#include "dialog.hpp"

using namespace genv;

enum Players {
    X = 0,
    O = 1
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
    int amountToWin= 4;
    int cellNumber = 15;
    Dialog* menu;
    Players currentPlayer = Players::X;
    Button*** cells;
    virtual void createMenu();
    virtual void openMainMenu();
    virtual void reset();
    virtual void checkWinningConditions();
    virtual void createMap();
    virtual void handleWin();

};

#endif
