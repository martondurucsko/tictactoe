#include "gamemanager.hpp"
#include "selector.hpp"
#include "statictext.hpp"

GameManager::GameManager(std::vector<Widget*>& w, int x,int y, int width, int height) : w(w), x(x), y(y), width(width), height(height) {
    int widgetHeight = 50;
    int widgetWidth = 200;
    new Button(w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 + widgetHeight + 30, widgetWidth, widgetHeight, "Play", [=]() {
        createMap();

        if (currentGameMode == GameModes::AvA) {
            startAILoop();
        }
    });
    new StaticText(w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 - widgetHeight - 10, "Map Size");
    new StaticText(w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 + 15, "Game Mode");
    Selector* modeSelector = new Selector(w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 + 20, widgetWidth, widgetHeight, {"Player vs Player", "Player vs AI", "AI vs AI"});
    modeSelector->setOnChange([=]() {
        switch(modeSelector->getSelectedIndex()) {
        case 0:
            currentGameMode = GameModes::PvP;
            break;
        case 1:
            currentGameMode = GameModes::PvA;
            break;
        case 2:
            currentGameMode = GameModes::AvA;
            break;
        }
    });
    Selector* sizeSelector = new Selector (w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 - widgetHeight - 5, widgetWidth, widgetHeight, {"15x15", "30x30"});
    sizeSelector->setOnChange([=]() {
        switch(sizeSelector->getSelectedIndex()) {
        case 0:
            cellNumber = 15;
            break;
        case 1:
            cellNumber = 30;
            break;
        }
    });
}

void GameManager::reset() {
    for (int x = 0; x < cellNumber; x++) {
        for (int y = 0; y < cellNumber; y++) {
            cells[x][y]->setText("");
        }
    }
}

void GameManager::checkWinningConditions() {
    if (!movesLeft()) {
        handleWin(true);
        return;
    }

    //Horizontal, Vertical
    for (int x = 0; x < cellNumber; x++) {
        int horizontalX=0;
        int horizontalO=0;
        int verticalX=0;
        int verticalO=0;
        for (int y = 0; y < cellNumber; y++) {
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
            else {
                horizontalO = 0;
                horizontalX = 0;
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
            else {
                verticalO = 0;
                verticalX = 0;
            }


            if (horizontalX == amountToWin || verticalX == amountToWin || horizontalO == amountToWin || verticalO == amountToWin) {
                handleWin(false);
            }
        }
    }

    //Left diagonal
    for (int x = 0; x < cellNumber; x++) {
        for (int y = 0; y < cellNumber; y++) {
            int maxStepX = cellNumber - x;
            int maxStepY = cellNumber - y;
            if (maxStepX < amountToWin || maxStepY < amountToWin)
            {
                break;
            }


            int leftDiagonalX = 0;
            int leftDiagonalO = 0;
            for (int i = 0; i < amountToWin; i++) {
                Button* cell = cells[x+i][y+i];
                if(cell->getText() != ""){
                    if(cell->getText() == "X"){
                        leftDiagonalX++;
                        leftDiagonalO = 0;
                    }
                    else{
                        leftDiagonalO++;
                        leftDiagonalX = 0;
                    }
                }
                else {
                    leftDiagonalO = 0;
                    leftDiagonalX = 0;
                }
                if(leftDiagonalO >= amountToWin || leftDiagonalX >= amountToWin){
                    handleWin(false);
                }
            }
        }
    }
    //Right diagonal
    for (int x = 0; x < cellNumber; x++) {
        for (int y = 0; y < cellNumber; y++) {
            int maxStepX = cellNumber - y;
            if (maxStepX < amountToWin)
            {
                continue;
            }

            int rightDiagonalX = 0;
            int rightDiagonalO = 0;
            for (int i = 0; i < amountToWin; i++) {
                if (x - i < 0 || y + i < 0){
                    break;
                }
                Button* cell = cells[y+i][x-i];
                if(cell->getText() != ""){
                    if(cell->getText() == "X"){
                        rightDiagonalX++;
                        rightDiagonalO = 0;
                    }
                    else{
                        rightDiagonalO++;
                        rightDiagonalX = 0;
                    }
                }
                else {
                    rightDiagonalO = 0;
                    rightDiagonalX = 0;
                }
                if(rightDiagonalO >= amountToWin || rightDiagonalX >= amountToWin){
                    handleWin(false);
                }
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

    for (int i = 0; i < cellNumber; i++) {
        for (int j = 0; j < cellNumber; j++) {
            Button* cell =  new Button(w, x + cellWidth * i, y + cellHeight * j, cellWidth, cellHeight);
            if (currentGameMode == GameModes::PvP) {
                cell->setOnClick([=]() {
                    if (cell->getText() == "") {
                        std::string player = currentPlayer == Players::X ? "X" : "O";
                        cell->setText(player);
                        currentPlayer = currentPlayer == Players::X ? Players::O : Players::X;
                        checkWinningConditions();
                    }
                });
            }
            if (currentGameMode == GameModes::PvA) {
                cell->setOnClick([=]() {
                    if (cell->getText() == "") {
                        cell->setText("X");
                        currentPlayer = Players::O;
                        renderMap();
                        checkWinningConditions();
                        makeAIMove();
                    }
                });
            }
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
        for (int i = 0; i < cellNumber; i++) {
            for (int j = 0; j < cellNumber; j++) {
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
        for (int i = 0; i < cellNumber; i++) {
            for (int j = 0; j < cellNumber; j++) {
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

void GameManager::handleWin(bool isDraw) {
    for (int i = 0; i < cellNumber; i++) {
        for (int j = 0; j < cellNumber; j++) {
            Button* c = cells[i][j];
            c->setEnable(false);
        }
    }
    menu->setText(isDraw ? "Draw" : (currentPlayer == Players::X ? "O has won" : "X has won"));
    menu->setVisible(true);
    menu->setEnable(true);
    currentPlayer = Players::X;
}

int GameManager::evaluate() {
    // Horizontal and Vertical checks
    for (int x = 0; x < cellNumber; x++) {
        int horizontalX = 0, horizontalO = 0;
        int verticalX = 0, verticalO = 0;

        for (int y = 0; y < cellNumber; y++) {
            // Horizontal check
            Button* cellHorizontal = cells[y][x];
            if (cellHorizontal->getText() != "") {
                if (cellHorizontal->getText() == "X") {
                    horizontalX++;
                    horizontalO = 0;
                } else {
                    horizontalO++;
                    horizontalX = 0;
                }
            }
            else {
                horizontalX = 0;
                horizontalO = 0;
            }

            if (horizontalX >= amountToWin) return -10;
            if (horizontalO >= amountToWin) return 10;

            // Vertical check
            Button* cellVertical = cells[x][y];
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
            else {
                verticalX = 0;
                verticalO = 0;
            }

            if (verticalX >= amountToWin) return -10;
            if (verticalO >= amountToWin) return 10;
        }
    }

    for (int x = 0; x < cellNumber; x++) {
        for (int y = 0; y < cellNumber; y++) {
            int maxStepX = cellNumber - x;
            int maxStepY = cellNumber - y;
            if (maxStepX < amountToWin || maxStepY < amountToWin)
                continue;

            int leftDiagonalX = 0, leftDiagonalO = 0;
            for (int i = 0; i < amountToWin; i++) {
                Button* cell = cells[x + i][y + i];
                if (cell->getText() != "") {
                    if (cell->getText() == "X") {
                        leftDiagonalX++;
                        leftDiagonalO = 0;
                    }
                    else {
                        leftDiagonalO++;
                        leftDiagonalX = 0;
                    }
                }
                else {
                    leftDiagonalX = 0;
                    leftDiagonalO = 0;
                }
                if (leftDiagonalX >= amountToWin) return -10;
                if (leftDiagonalO >= amountToWin) return 10;
            }
        }
    }

    for (int x = 0; x < cellNumber; x++) {
        for (int y = 0; y < cellNumber; y++) {
            int maxStepX = cellNumber - y;
            if (maxStepX < amountToWin)
                continue;

            int rightDiagonalX = 0, rightDiagonalO = 0;
            for (int i = 0; i < amountToWin; i++) {
                if (x - i < 0 || y + i >= cellNumber)
                    break;

                Button* cell = cells[y + i][x - i];
                if (cell->getText() != "") {
                    if (cell->getText() == "X") {
                        rightDiagonalX++;
                        rightDiagonalO = 0;
                    }
                    else {
                        rightDiagonalO++;
                        rightDiagonalX = 0;
                    }
                }
                else {
                    rightDiagonalX = 0;
                    rightDiagonalO = 0;
                }
                if (rightDiagonalX >= amountToWin) return -10;
                if (rightDiagonalO >= amountToWin) return 10;
            }
        }
    }

    return 0;
}

bool GameManager::movesLeft() {
    for (int x = 0; x < cellNumber; x++) {
        for (int y = 0; y < cellNumber; y++) {
            Button* cell = cells[y][x];
            if (cell->getText() == "") {
                return true;
            }
        }
    }
    return false;
}

int GameManager::minimax(int depth, bool isMax, int alpha, int beta, int maxDepth) {
    int score = evaluate();

    if (score == 10) {
        return score - depth;
    }

    if (score == -10) {
        return score + depth;
    }

    if (!movesLeft())
        return 0;

    if (depth >= maxDepth)
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < cellNumber; i++) {
            for (int j = 0; j < cellNumber; j++) {
                Button* cell = cells[i][j];
                if (cell->getText() == "") {
                    cell->setText("O");
                    int moveVal = minimax(depth + 1, !isMax, alpha, beta, maxDepth);
                    best = std::max(best, moveVal);
                    cell->setText("");
                    alpha = std::max(alpha, best);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for (int i = 0; i < cellNumber; i++) {
            for (int j = 0; j < cellNumber; j++) {
                Button* cell = cells[i][j];
                if (cell->getText() == "") {
                    cell->setText("X");
                    int moveVal = minimax(depth + 1, !isMax, alpha, beta, maxDepth);
                    best = std::min(best, moveVal);
                    cell->setText("");
                    beta = std::min(beta, best);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    }
}

Position GameManager::findBestMove() {
    int bestVal = -1000;
    Position bestMove = Position(-1, -1);

    int maxDepth = 1;

    for (int i = 0; i < cellNumber; i++) {
        for (int j = 0; j < cellNumber; j++) {
            Button* cell = cells[i][j];
            if (cell->getText() == "") {
                cell->setText("O");
                int moveVal = minimax(0, false, -1000, 1000, maxDepth);
                cell->setText("");

                if (moveVal > bestVal) {
                    bestMove = Position(i, j);
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void GameManager::renderMap() {
    for (int x = 0; x < cellNumber; x++) {
        for (int y = 0; y < cellNumber; y++) {
            Button* cell = cells[x][y];
            cell->draw();
        }
    }
    gout << refresh;
}

void GameManager::startAILoop() {
    while (true) {
        makeAIMove();
        checkWinningConditions();
        if (!movesLeft() || menu->getEnable()) {
            break;
        }
        if (currentGameMode == GameModes::AvA) {
            currentPlayer = currentPlayer == Players::X ? Players::O : Players::X;
        }
    }
}

void GameManager::makeAIMove() {
    Position aiPosition = findBestMove();
    string player = currentPlayer == Players::X ? "X" : "O";
    cells[aiPosition.x][aiPosition.y]->setText(player);
    renderMap();
}

