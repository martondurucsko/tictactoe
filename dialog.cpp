#include "dialog.hpp"
#include "button.hpp"

Dialog::Dialog(std::vector<Widget*>& w, int x,int y, int width, int height) : Widget(w, x, y, width, height)
{

}

Dialog::Dialog(std::vector<Widget*>& w, int x, int y, int width, int height, string text) : Widget(w, x, y, width, height) {
    this->text = text;
}

Dialog::Dialog(std::vector<Widget*>& w, int x, int y, int width, int height, string text, Option button1) : Widget(w, x, y, width, height) {
    this->text = text;
    int buttonWidth = gout.twidth(button1.getText()) + 15;
    int buttonHeight = 40;
    Button* b1 = new Button(w, x + (height - buttonHeight) - 15 , y + (height - buttonHeight) - 15 ,buttonWidth ,buttonHeight, button1.getText(), button1.getOnClick());
    children.push_back(b1);
}

Dialog::Dialog(std::vector<Widget*>& w, int x, int y, int width, int height, string text, Option button1, Option button2) : Widget(w, x, y, width, height) {
    this->text = text;
    int button1Width = gout.twidth(button1.getText()) + 15;
    int button2Width = gout.twidth(button2.getText()) + 15;
    int buttonHeight = 40;
    Button* b1 = new Button(w, x + (height - buttonHeight) - 20 , y + (height - buttonHeight) - 15 ,button1Width ,buttonHeight, button1.getText(), button1.getOnClick());
    children.push_back(b1);
    Button* b2 = new Button(w, x + 15 , y + (height - buttonHeight) - 15, button2Width, buttonHeight, button2.getText(), button2.getOnClick());
    children.push_back(b2);
}

void Dialog::draw(){
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

void Dialog::handle(event ev){

}

string Dialog::to_string(){

}


void Dialog::setText(string text){
    this->text = text;
}

string Dialog::getText(){
    return text;
}
