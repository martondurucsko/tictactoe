#include "statictext.hpp"

using namespace genv;

StaticText::StaticText(std::vector<Widget*>& w, int x, int y, std::string text) : Widget(w, x, y, 0, 0)
{
    this->text = text;
}

void StaticText::draw()
{
    gout << move_to(x, y) << color(255,255,255) << genv::text(text);
}

void StaticText::handle(event ev)
{

}

std::string StaticText::getText() {
    return text;
}

void StaticText::setText(std::string text) {
    this->text = text;
}

std::string StaticText::to_string() {
    return text;
}
