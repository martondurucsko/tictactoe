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
    for (int x = 0; x < cellNumber; ++x) {
        for (int y = 0; y < cellNumber; ++y) {
            cells[x][y]->setText("");
        }
    }
}

void GameManager::checkWinningConditions() {
    for (int x = 0; x < cellNumber; ++x) {
        int horizontalX=0;
        int horizontalO=0;
        int verticalX=0;
        int verticalO=0;
        for (int y = 0; y < cellNumber; ++y) {
            Button* cellHorizontal=cells[y][x];
            Button* cellVertical=cells[x][y];
            if (cellHorizontal->getText() != ""){
                if (cellHorizontal->getText() == "X") {
                    horizontalX++;
                    horizontalO = 0;
                }
                else {
                    horizontalO++;
                    horizontalX = 0;

                }
            }
            if (cellVertical->getText() != "") {
                if (cellVertical->getText() == "X") {
                    verticalX++;
                    verticalO = 0;
                }
                else {
                    verticalO++;
                    verticalX = 0;
                }
            }
            if (horizontalX == 4 || verticalX == 4 || horizontalO == 4 || verticalO == 4) {
                //std::cout << (currentPlayer == Players::X ? "X has won" : "O has won") << std::endl;
                handleWin();
            }
        }
    }
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
                    checkWinningConditions();
                    currentPlayer = currentPlayer == Players::X ? Players::O : Players::X;
                }
            });
            cells[i][j] = cell;
        }
    }
    createMenu();
}

void GameManager::createMenu(){
    int menuWidth = 180;
    int menuHeight = 180;
    Option button1 = Option("menu", [=]() {
        openMainMenu();
    });
    Option button2 = Option("rematch", [&]() {
        menu->setVisible(false);
        menu->setEnable(false);
        reset();
        for (int i = 0; i < cellNumber; ++i) {
            for (int j = 0; j < cellNumber; ++j) {
                Button* c = cells[i][j];
                c->setEnable(true);
            }
        }
    });
    menu = new Dialog(w,width/2 - menuWidth / 2, height/2 - menuHeight / 2, menuWidth, menuHeight, "", button1, button2);
    menu->setVisible(false);
    menu->setEnable(false);
}

void GameManager::openMainMenu(){
    if(cells!=nullptr){
        for (int i = 0; i < cellNumber; ++i) {
            for (int j = 0; j < cellNumber; ++j) {
                Button* cell = cells[i][j];
                cell->setEnable(false);
                cell->setVisible(false);
                delete cell;
            }
            delete[] cells[i];
        }
        delete[] cells;
        cells = nullptr;
    }
    menu->setVisible(false);
    menu->setEnable(false);
}

void GameManager::handleWin() {
    for (int i = 0; i < cellNumber; ++i) {
        for (int j = 0; j < cellNumber; ++j) {
            Button* c = cells[i][j];
            c->setEnable(false);
        }
    }
    menu->setText(currentPlayer == Players::X ? "X has won" : "O has won");
    menu->setVisible(true);
    menu->setEnable(true);
    //TODO: This doesnt seems to work in case the user went back to menu
    currentPlayer = Players::X;
}

std::string GameManager::to_string() {
    return "";
}

