#include "graphics.hpp"

#include "gamemanager.hpp"
#include "widget.hpp"

#include <vector>

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

    new GameManager(w, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    //Draw scene before first event
    for (Widget* wg : w) {
        wg->draw();
    }

    gout << refresh;

    event_loop(w);

    return 0;
}

