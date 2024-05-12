#include "widget.hpp"

#include <functional>
#include <vector>

using namespace std;

Widget::Widget(std::vector<Widget*>& w, int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height), w(w) {
    w.push_back(this);
}

Widget::~Widget() {
    std::vector<Widget*>::iterator it = std::find(w.begin(), w.end(), this);
    if (it != w.end()) {
        w.erase(it);
    }
}

bool Widget::is_selected(int mouse_x, int mouse_y)
{
    return (mouse_x <= (x + width) && mouse_x>=x && mouse_y <= (y + height) && y <= mouse_y);
}

bool Widget::getVisible()
{
    return visible;
}

void Widget::setVisible(bool visible)
{
    for (Widget* c : children) {
        c->setVisible(visible);
    }
    this->visible = visible;
}

bool Widget::getEnable()
{
    return enable;
}

void Widget::setEnable(bool enable)
{
    for (Widget* c : children) {
        c->setEnable(enable);
    }
    this->enable = enable;
}

Position Widget::getPosition()
{
    return Position(x, y);
}

void Widget::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

Size Widget::getSize()
{
    return Size(width, height);
}

void Widget::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}
