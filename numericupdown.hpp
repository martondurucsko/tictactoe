#pragma once

#include <functional>

#include "widget.hpp"

using namespace genv;
using namespace std;

class NumericUpDown : public Widget
{
public:
    NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height);
    NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height, int value);
    NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height, int value, int stepValue);
    NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height, int value, int stepValue, int minValue, int maxValue);
    virtual void handle(genv::event ev);
    virtual void draw();
    virtual std::string to_string();
    virtual int getValue();
    virtual void setValue(int value);
    virtual void init(std::vector<Widget*>& w);
    virtual int getMaxValue();
    virtual void setMaxValue(int value);
    virtual int getMinValue();
    virtual void setMinValue(int value);
    virtual function<void()> getOnChange();
    virtual void setOnChange(function<void()> onChange);
protected:
    int value = 0;
    int prevValue = 0;
    int stepValue = 1;
    int maxValue = INT_MAX;
    int minValue = INT_MIN;
    function<void()> onChange = []() {};
};

