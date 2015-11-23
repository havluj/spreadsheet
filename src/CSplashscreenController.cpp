/* 
 * File:   SplashscreenController.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 5, 2015, 1:46 AM
 */

#include "CSplashscreenController.h"

void CSplashscreenController::redraw() {
    clear();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    init_pair(2, COLOR_RED, COLOR_WHITE);
    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(0, 1, "Your terminal window is too small!");
    attroff(A_BOLD | COLOR_PAIR(2));

    mvprintw(2, 1, "Make sure it is at least 78x27.");
    mvprintw(3, 1, "Try resizing it.");


    attrset(COLOR_PAIR(1));
    mvprintw(maxY - 1, 1, " F4 - exit ");
    attroff(COLOR_PAIR(1));

    refresh();
}

