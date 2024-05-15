#ifndef STATIC_HPP
#define STATIC_HPP

#include "widget.hpp"

class StaticText : public Widget
{
public:
    StaticText(std::vector<Widget*>& w, int x, int y, std::string text);
    virtual void draw() override;
    virtual void handle(genv::event ev);
    virtual std::string to_string();
    virtual std::string getText();
    virtual void setText(std::string text);
protected:
    std::string text = "";
};

#endif
