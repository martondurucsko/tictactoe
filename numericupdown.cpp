#include "numericupdown.hpp"
#include "button.hpp"

NumericUpDown::NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height) : Widget(w,x,y,width,height) {
    init(w);
}

NumericUpDown::NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height,int value) : Widget (w,x,y,width,height){
    this->value = value;
    init(w);
}

NumericUpDown::NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height,int value, int stepValue) : Widget(w,x,y,width,height) {
    this->value = value;
    this->stepValue = stepValue;
    init(w);
}

NumericUpDown::NumericUpDown(std::vector<Widget*>& w, int x,int y, int width, int height, int value, int stepValue, int minValue, int maxValue) : Widget(w,x,y,width,height) {
    this->value = value;
    this->stepValue = stepValue;
    this->minValue = minValue;
    this->maxValue = maxValue;
    init(w);
}

void NumericUpDown::init(std::vector<Widget*>& w){
    Button* b1 = new Button(w,(x+width)-height,y,height, height/2,"+", [=]() {
        setValue(value + stepValue);
    });
    children.push_back(b1);
    Button* b2 = new Button(w,(x+width)-height,y+(height/2)-2,height, (height/2)+2,"-", [=]() {
        setValue(value - stepValue);
    });
    children.push_back(b2);
}

void NumericUpDown::draw()
{
    if (!visible) {
        return;
    }

    int rgb = enable ? 255 : 40;

    gout << move_to(x, y) << color(rgb, rgb, rgb) << box(width, height);
    gout << move_to(x + 2, y + 2) << color(0,0,0) << box(width - 4, height - 4);
    int text_x = (x + (width - gout.twidth(std::to_string(value))) / 2) - height/2;
    int text_y = y + height / 2 + (gout.cascent() - gout.cdescent()) / 2;
    gout << move_to(text_x,text_y) << color(rgb, rgb, rgb) << genv::text(std::to_string(value));
}
void NumericUpDown::handle(genv::event ev) {
    if (!enable) {
        return;
    }

    if (ev.type == ev_key) {
        if (ev.keycode == key_up || ev.keycode == key_pgup) {
            setValue(value + stepValue);
        }
        else if (ev.keycode == key_down || ev.keycode == key_pgdn) {
            setValue(value - stepValue);
        }
    }

    draw();
}

int NumericUpDown::getValue () {
    return value;
}
void NumericUpDown::setValue (int value) {
    if (value <= maxValue && value >= minValue) {
        this->value = value;
    }
}
int NumericUpDown::getMaxValue() {
    return value;
}
void NumericUpDown::setMinValue(int minValue) {
    this->minValue = minValue;
    if (value < minValue)
        value = minValue;
}
void NumericUpDown::setMaxValue(int maxValue) {
    this->maxValue = maxValue;
    if (value > maxValue)
        value = maxValue;
}
int NumericUpDown::getMinValue() {
    return minValue;
}
std::string NumericUpDown::to_string() {
    return "NumericUpDown: Value: " + std::to_string(value) + ", StepValue: " + std::to_string(stepValue) + ", Intervall: [" + std::to_string(minValue) +", "+ std::to_string(maxValue) + "]";
}
