#pragma once

#include <functional>

#include "widget.hpp"

class Button : public Widget
{
public:
    Button(vector<Widget*>& w, int x, int y, int width, int height);
    Button(vector<Widget*>& w, int x, int y, int width, int height, std::string text);
    Button(vector<Widget*>& w, int x, int y, int width, int height, std::string text, std::function<void()> onClick);
    virtual void handle(genv::event ev);
    virtual void draw();
    virtual std::string to_string();
    virtual std::string getText();
    virtual void setText(string text);
    virtual void setOnClick(std::function<void()> onClick);
protected:
    std::string text = "";
    std::function<void()> onClick = []() {};
};

