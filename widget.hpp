#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"

using namespace std;

struct Position
{
public:
    int x, y;
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

struct Size
{
public:
    int width, height;
    Size(int width, int height) {
        this->width = width;
        this->height = height;
    }
};

class Widget
{
public:
    Widget(std::vector<Widget*>& w, int x,int y, int width, int height);
    virtual ~Widget();
    virtual void handle(genv::event ev) = 0;
    virtual void draw () = 0;
    virtual std::string to_string() = 0;
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual bool getVisible();
    virtual void setVisible(bool visible);
    virtual bool getEnable();
    virtual void setEnable(bool enable);
    virtual Position getPosition();
    virtual void setPosition(int x, int y);
    virtual Size getSize();
    virtual void setSize(int width, int height);

protected:
    int x;
    int y;
    int width;
    int height;
    bool visible = true;
    bool enable = true;
    std::vector<Widget*>& w;
    std::vector<Widget*> children = {};
};

#endif
