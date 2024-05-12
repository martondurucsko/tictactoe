#include "selector.hpp"

Selector::Selector(std::vector<Widget*>& w, int x,int y, int width, int height) : Widget(w, x, y, width, height) {
    init(w);
}

Selector::Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options) : Widget(w, x, y, width, height) {
    for (int i = 0; i < (int)options.size(); i++) {
        Button* option = new Button(w, x, y + height * (i + 1), width, height + 2, options[i]);
        option->setOnClick([=]() {
            isOpen = !isOpen;
            selectedIndex = i;
        });
        option->setEnable(false);
        option->setVisible(false);

        this->options.push_back(option);
    }
    init(w);
}

Selector::Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options, int maxLines) : Widget(w, x, y, width, height) {
    for (int i = 0; i < (int)options.size(); i++) {
        Button* option = new Button(w, x, y + height * (i + 1), width, height + 2, options[i]);
        option->setOnClick([=]() {
            isOpen = !isOpen;
            selectedIndex = i;
        });
        option->setEnable(false);
        option->setVisible(false);

        this->options.push_back(option);
    }
    this->maxLines = maxLines;
    init(w);
}

Selector::Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options, int maxLines, int scrollValue) : Widget(w, x, y, width, height) {
    for (int i = 0; i < (int)options.size(); i++) {
        Button* option = new Button(w, x, y + height * (i + 1), width, height + 2, options[i]);
        option->setOnClick([=]() {
            isOpen = !isOpen;
            selectedIndex = i;
        });
        option->setEnable(false);
        option->setVisible(false);

        this->options.push_back(option);
    }
    this->maxLines = maxLines;
    this->scrollValue = scrollValue;
    init(w);
}
Selector::Selector(std::vector<Widget*>& w, int x,int y, int width, int height, vector<string> options, int maxLines, int scrollValue, int selectedIndex) : Widget(w, x, y, width, height) {
    for (int i = 0; i < (int)options.size(); i++) {
        Button* option = new Button(w, x, y + height * (i + 1), width, height + 2, options[i]);
        option->setOnClick([=]() {
            isOpen = !isOpen;
            this->selectedIndex = i;
        });
        option->setEnable(false);
        option->setVisible(false);

        this->options.push_back(option);
    }
    this->maxLines = maxLines;
    this->scrollValue = scrollValue;
    this->selectedIndex = selectedIndex;
    init(w);
}

void Selector::init(vector<Widget*>& w) {
    openCloseButton = new Button(w,x+(width-height),y,height,height,"\\/");
    openCloseButton->setOnClick([&]() {
        isOpen = !isOpen;
        openCloseButton->setText( isOpen ? "/\\":"\\/");
    });
    children.push_back(openCloseButton);
    renderOptions();
}

void Selector::draw() {
    if (prevSelectedIndex != selectedIndex) {
        prevSelectedIndex = selectedIndex;
        onChange();
    }

    if (!visible) {
        return;
    }

    if (prevIsOpen != isOpen) {
        prevIsOpen = isOpen;
        renderOptions();
    }

    int rgb = enable ? 255 : 40;
    string text = getValue();

    gout << move_to(x, y) << color(rgb, rgb, rgb) << box(width, height);
    gout << move_to(x + 2, y + 2) << color(0,0,0) << box(width - 4, height - 4);

    int text_x = (x + (width - gout.twidth(text)) / 2) - height/2;
    int text_y = y + height / 2 + (gout.cascent() - gout.cdescent()) / 2;

    gout << move_to(text_x,text_y) << color(rgb, rgb, rgb) << genv::text(text);
}

void Selector::add(string option) {
    int i = options.size();
    Button* b = new Button(w, x, y + height * (i + 1), width, height + 2, option);
    b->setOnClick([=]() {
        isOpen = !isOpen;
        selectedIndex = options.size() - 1;
    });
    b->setEnable(false);
    b->setVisible(false);

    options.push_back(b);
    renderOptions();
}

std::string Selector::remove(int index) {
    if (options.size() < index + 1) {
        return "Index was out of range";
    }

    std::string removedElement;
    vector<string> tmpOptions;

    for (int i = 0; i < options.size(); i++) {
        Button* o = options[i];
        if (i != index) {
            tmpOptions.push_back(o->getText());
        } else {
            removedElement = o->getText();
        }
    }

    for (Button* o : options) {
        delete o;
    }

    options.clear();

    for (int i = 0; i < tmpOptions.size(); i++) {
        Button* option = new Button(w, x, y + height * (i + 1), width, height + 2, tmpOptions[i]);
        option->setOnClick([=]() {
            isOpen = !isOpen;
            selectedIndex = i;
        });
        option->setEnable(false);
        option->setVisible(false);

        options.push_back(option);
    }

    if (index < selectedIndex) {
        selectedIndex--;
    }


    renderOptions();
    return removedElement;
}

void Selector::handle(genv::event ev) {
    if (!isOpen)
        return;

    if (ev.type == ev_mouse && (ev.button == btn_wheelup || ev.button == btn_wheeldown)) {
        if (ev.button == btn_wheelup) {
            if (scrollValue + 1 > 0)
                return;

            scrollValue += 1;

            for (Button* option : options) {
                Position p = option->getPosition();
                option->setPosition(p.x, p.y + height);
            }
        }
        if (ev.button == btn_wheeldown) {
            if (maxLines >= (int)options.size() + scrollValue)
                return;

            scrollValue -= 1;

            for (Button* option : options) {
                Position p = option->getPosition();
                option->setPosition(p.x, p.y - height);
            }
        }
        renderOptions();
    }
}

void Selector::renderOptions() {
    for (Button* o : options) {
        Position p = o->getPosition();
        if (p.y <= y || p.y >= y + height * maxLines + 1) {
            o->setVisible(false);
            o->setEnable(false);
        } else {
            o->setVisible(visible ? isOpen : false);
            o->setEnable(enable ? isOpen : false);
        }
    }
}

void Selector::setVisible(bool visible) {
    for (Widget* c : children) {
        c->setVisible(visible);
    }
    this->visible = visible;
    renderOptions();
}

void Selector::setEnable(bool enable) {
    for (Widget* c : children) {
        c->setEnable(enable);
    }
    this->enable = enable;
    renderOptions();
}

std::string Selector::getValue() {
    return options.size() == 0 ? "<empty>" : options[selectedIndex]->getText();
}

int Selector::getSelectedIndex(){
    return selectedIndex;
}

void Selector::setSelectedIndex(int selectedIndex){
    this->selectedIndex = selectedIndex;
}

int Selector::getMaxLines(){
    return maxLines;
}

void Selector::setMaxLines(int maxLines){
    this->maxLines = maxLines;
}

int Selector::getScrollValue(){
    return scrollValue;
}

void Selector::setScrollValue(int scrollValue){
    this->scrollValue = scrollValue;
}

bool Selector::getIsOpen(){
    return isOpen;
}

void Selector::setIsOpen(bool isOpen){
    this->isOpen = isOpen;
}
vector<string> Selector::getOptions(){
    vector<string> tmpOptions;
    for(Button* i : options) {
        i->getText();
        tmpOptions.push_back(i->getText());
    }
    return tmpOptions;
}
void Selector::setOptions(vector<string> options) {
    for (Button* o : this->options) {
        delete o;
    }

    this->options.clear();

    for (int i = 0; i < (int)options.size(); i++) {
        Button* option = new Button(w, x, y + height * (i + 1), width, height + 2, options[i]);
        option->setOnClick([=]() {
            isOpen = !isOpen;
            selectedIndex = i;
        });
        option->setEnable(false);
        option->setVisible(false);

        this->options.push_back(option);
    }

    renderOptions();
}

string Selector::to_string(){

    string elements;

    if (options.size() > 0) {
        elements = options[0]->getText();
        for(int i = 1; i < (int)options.size(); i++) {
            elements += ", " + options[i]->getText();
        }
    }

    return "Selector: Value: " + getValue() + ", selectedIndex: " + std::to_string(selectedIndex) + ", Elements: {" + elements + "}";
}

function<void()> Selector::getOnChange(){
    return onChange;
}

void Selector::setOnChange(function<void()> onChange){
    this->onChange = onChange;
}
