#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "widget.hpp"
#include "button.hpp"
#include "dialog.hpp"

using namespace genv;

enum Players {
    X = 0,
    O = 1
};

class GameManager : public Widget
{
public:
    GameManager(std::vector<Widget*>& w, int x,int y, int width, int height);
    virtual void handle(event ev);
    virtual std::string to_string();
    virtual void draw();
protected:
    Dialog* menu;
    int cellNumber = 15;
    int amountToWin= 4;
    Players currentPlayer = Players::X;
    Button*** cells;
    virtual void createMenu();
    virtual void init();
    virtual void openMainMenu();
    virtual void reset();
    virtual void checkWinningConditions();
    virtual void createMap();
    virtual void handleWin();

};

#endif
