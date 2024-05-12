#include "gamemanager.hpp"
#include "selector.hpp"

GameManager::GameManager(std::vector<Widget*>& w, int x,int y, int width, int height) : Widget(w, x, y, width, height)
{
    init();
}

void GameManager::init() {
//play button palya selecto
    int widgetHeight = 50;
    int widgetWidth = 180;
    Button* p = new Button(w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2, widgetWidth, widgetHeight, "Play");
    Selector* s = new Selector (w, width / 2 - widgetWidth / 2, height / 2 - widgetWidth / 2 - widgetHeight - 5, widgetWidth, widgetHeight, {"Alma", "Labda", "Banan", "Kocsi"});
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

}

void GameManager::handleWin() {

}

std::string GameManager::to_string() {
    return "";
}

