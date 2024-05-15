#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include <iostream>
#include <functional>

#include "widget.hpp"
#include "button.hpp"

using namespace genv;

class Selector : public Widget
{
public:
    Selector(std::vector<Widget*>& w, int x,int y, int width, int height);
    Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options);
    Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options, int maxLines);
    Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options, int maxLines, int scrollValue);
    Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options, int maxLines, int scrollValue, int selectedIndex);
    virtual void handle(genv::event ev);
    virtual void draw();
    virtual void renderOptions();
    virtual void add(std::string option);
    virtual std::string remove(int index);
    virtual std::string to_string();
    virtual std::string getValue();
    virtual int getSelectedIndex();
    virtual void setSelectedIndex(int selectedIndex);
    virtual int getMaxLines();
    virtual void setMaxLines(int maxLines);
    virtual int getScrollValue();
    virtual void setScrollValue(int scrollValue);
    virtual bool getIsOpen();
    virtual void setIsOpen(bool isOpen);
    virtual void setVisible(bool visible);
    virtual void setEnable(bool enable);
    virtual vector<string> getOptions();
    virtual void setOptions(vector<string> options);
    virtual function<void()> getOnChange();
    virtual void setOnChange(function<void()> onChange);

protected:
    int selectedIndex = 0;
    int prevSelectedIndex = 0;
    int maxLines = 4;
    int scrollValue = 0;
    bool isOpen = false, prevIsOpen = false;
    Button* openCloseButton;
    vector<Button*> options = {};
    virtual void init(std::vector<Widget*>& w);
    function<void()> onChange = []() {};
};

#endif
