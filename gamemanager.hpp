#pragma once

#include "widget.hpp"
#include "button.hpp"

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
    int cellNumber = 15;
    Players currentPlayer = Players::X;
    Button*** cells;
    virtual void init();
    virtual void reset();
    virtual void checkWinningConditions();
    virtual void createMap();
    virtual void handleWin();
};

