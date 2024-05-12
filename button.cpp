#include "button.hpp"

using namespace std;
using namespace genv;

Button::Button(vector<Widget*>& w, int x, int y, int width, int height) : Widget(w,x,y,width,height)
{

}
Button::Button(vector<Widget*>& w, int x, int y, int width, int height, std::string text) : Widget(w,x,y,width, height)
{
    this->text = text;
}
Button::Button(std::vector<Widget*>& w, int x, int y, int width, int height, std::string text, std::function<void()> onClick) : Widget(w, x, y, width, height)
{
    this->text = text;
    this->onClick = onClick;
}

void Button::handle(genv::event ev)
{
    if (!enable) {
        return;
    }

    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y))
    {
        onClick();
    }
}

void Button::draw()
{
    if (!visible) {
        return;
    }

    int rgb = enable ? 255 : 40;

    gout << move_to(x, y) << color(rgb, rgb, rgb) << box(width, height);
    gout << move_to(x + 2, y + 2) << color(0,0,0) << box(width - 4, height - 4);
    int text_x = x + (width - gout.twidth(text)) / 2;
    int text_y = y + height / 2 + (gout.cascent() - gout.cdescent()) / 2;
    gout << move_to(text_x,text_y) << color(rgb, rgb, rgb) << genv::text(text);
}

std::string Button::getText() {
    return text;
}
void Button::setText(string text) {
    this->text = text;
}

void Button::setOnClick(std::function<void()> onClick) {
    this->onClick = onClick;
}

std::string Button::to_string()
{
    return "Button: Text: " + text;
}
