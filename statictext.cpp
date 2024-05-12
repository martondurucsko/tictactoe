#include "statictext.hpp"
using namespace genv ;

StaticText::StaticText(int x,int y, int sx, int sy,std::string text):Widget(x,y,sx,sy),_text(text)
{

}

void StaticText::draw()
{
    gout << move_to(_x,_y)
         <<color(0,0,0)
         <<box(_size_x,_size_y)
         <<color(255,255,255)
         <<move_to(_x+5,_y+5)
         << text(_text);
}

void StaticText::handle(event ev)
{

}
