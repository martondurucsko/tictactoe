#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "widget.hpp"

#include <functional>

using namespace genv;

struct Option {
private:
    string text;
    function<void()> onClick;
public:
    Option(string text, function<void()> onClick) {
        this->text = text;
        this->onClick = onClick;
    }
    string getText() {
        return text;
    }
    void setText(string text) {
        this->text = text;
    }
    function<void()> getOnClick() {
        return onClick;
    }
    void setOnClick(function<void()> onClick) {
        this->onClick = onClick;
    }
};

class Dialog : public Widget
{
public:
    Dialog(std::vector<Widget*>& w, int x, int y, int width, int height);
    Dialog(std::vector<Widget*>& w, int x, int y, int width, int height, string text);
    Dialog(std::vector<Widget*>& w, int x, int y, int width, int height, string text, Option button1);
    Dialog(std::vector<Widget*>& w, int x, int y, int width, int height, string text, Option button1, Option button2);
    virtual void handle(event ev);
    virtual std::string to_string();
    virtual void draw();
    virtual string getText();
    virtual void setText(string text);
protected:
    string text = "";
};

#endif // DIALOG_HPP
