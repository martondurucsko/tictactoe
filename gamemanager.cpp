#include "gamemanager.hpp"
#include "selector.hpp"
#include "statictext.hpp"

GameManager::GameManager(std::vector<Widget*>& w, int x,int y, int width, int height) : Widget(w, x, y, width, height)
{
    init();
}

void GameManager::init() {
    int widgetHeight = 50;
    int widgetWidth = 180;
    new Button(w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2, widgetWidth, widgetHeight, "Play", [=]() { createMap(); });
    new StaticText(w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 - widgetHeight - 10, "Map Size");
    Selector* s = new Selector (w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 - widgetHeight - 5, widgetWidth, widgetHeight, {"15x15", "30x30"});
    s->setOnChange([=]() {
        switch(s->getSelectedIndex()) {
        case 0:
            cellNumber = 15;
            break;
        case 1:
            cellNumber = 30;
            break;
        }
    });
}

void GameManager::draw() {
}

void GameManager::handle(event ev) {

}


void GameManager::reset() {

}

void GameManager::checkWinningConditions() {

}

void GameManager::createMap() {
    cells = new Button**[cellNumber];
    for (int i = 0; i < cellNumber; i++) {
        cells[i] = new Button*[cellNumber];
    }

    int cellWidth = width / cellNumber;
    int cellHeight = height / cellNumber;

    for (int i = 0; i < cellNumber; ++i) {
        for (int j = 0; j < cellNumber; ++j) {
            Button* cell =  new Button(w, x + cellWidth * i, y + cellHeight * j, cellWidth, cellHeight);
            cell->setOnClick([=]() {
                if (cell->getText() == "") {
                    std::string player = currentPlayer == Players::X ? "X" : "O";
                    cell->setText(player);

                    currentPlayer = currentPlayer == Players::X ? Players::O : Players::X;
                }
            });
            cells[i][j] = cell;
        }
    }
}

void GameManager::handleWin() {

}

std::string GameManager::to_string() {
    return "";
}

