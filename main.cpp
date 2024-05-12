#include "graphics.hpp"

#include "widget.hpp"
#include "numericupdown.hpp"
#include "selector.hpp"

#include <vector>
#include <fstream>
#include <iostream>

using namespace genv;
using namespace std;

int const WINDOW_WIDTH = 600;
int const WINDOW_HEIGHT = 600;

void event_loop(vector<Widget*>& widgets) {
    event ev;
    int focus = -1;
    while(gin >> ev ) {
        gout << color(0, 0, 0) << move_to(0, 0) << box(WINDOW_WIDTH, WINDOW_HEIGHT);

        if (ev.type == ev_mouse && ev.button==btn_left) {
            for (size_t i = 0; i < widgets.size(); i++) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    if (!widgets[i]->getEnable())
                        continue;
                    focus = i;
                }
            }
        }
        if (focus!=-1) {
            widgets[focus]->handle(ev);
        }
        for (Widget* w : widgets) {
            w->draw();
        }
        gout << refresh;
    }
}

int main()
{
    gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);

    vector<Widget*> w;

    //Widget 1.
    NumericUpDown* n1 = new NumericUpDown(w, 50, 95, 200, 50, 0, 1, -10, 10);

    //Widget 2.
    NumericUpDown* n2 = new NumericUpDown(w, 260, 95, 200, 50, 1000, 10);

    //Selector 1.
    Selector* s1 = new Selector(w, 50, 155, 200, 50, {"Alma", "Korte", "Barack", "Szilva", "Fuge", "Gomba", "Dinnye", "Malna", "Bodza"});

    //Selector 2.
    Selector* s2 = new Selector(w, 260, 155, 200, 50, {"Kutya", "Macska", "Szarvas", "Tehen"});


    //Write to file button
    new Button(w, 10, (WINDOW_HEIGHT - 60), 50, 50, "Save", [&]() {
        std::ofstream output("ertekek.txt");
        if (output.is_open()) {
            output << "Raw values of widgets:" << std::endl << std::endl;
            output << "1. Widget " << std::endl << n1->getValue() << std::endl;
            output << "2. Widget " << std::endl << n2->getValue() << std::endl;
            output << "3. Widget " << std::endl << s1->getValue() << std::endl;
            output << "4. Widget " << std::endl << s2->getValue() << std::endl << std::endl;

            output << "toString values of widgets:" << std::endl << std::endl;
            output << "1. Widget " << std::endl << n1->to_string() << std::endl;
            output << "2. Widget " << std::endl << n2->to_string() << std::endl;
            output << "3. Widget " << std::endl << s1->to_string() << std::endl;
            output << "4. Widget " << std::endl << s2->to_string() << std::endl;


            output.close();
        }
    });

    //Show/Hide the 1. Selector
    Button* b1 = new Button(w, WINDOW_WIDTH - 70, WINDOW_HEIGHT - 50, 60, 40, "Hide", [&]() {
        s1->setVisible(!s1->getVisible());
        b1->setText(s1->getVisible() ? "Hide" : "Show");
    });

    //Enable/Disable the 1. Selector
    Button* b2 = new Button(w, WINDOW_WIDTH - 155, WINDOW_HEIGHT - 50, 80, 40, "Disable", [&]() {
        s1->setEnable(!s1->getEnable());
        b2->setText(s1->getEnable() ? "Disable" : "Enable");
    });

    //Set new values for the 1. Selector
    new Button(w, WINDOW_WIDTH - 210, WINDOW_HEIGHT - 50, 50, 40, "Set", [&]() {
        s1->setOptions({"Banan", "Mandarin", "Citrom", "Szolo", "Eper", "Kokusz"});
    });

    //Remove element from the 1. Selector by index. Value given by the 1. NumericUpDown
    new Button(w, WINDOW_WIDTH - 295, WINDOW_HEIGHT - 50, 80, 40, "Remove", [&]() {
        std::cout << s1->remove(n1->getValue()) << std::endl;

    });

    //Draw scene before first event
    for (Widget* wg : w) {
        wg->draw();
    }

    gout << refresh;

    event_loop(w);

    return 0;
}

