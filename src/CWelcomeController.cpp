/* 
 * File:   CWelcomeController.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 5, 2015, 2:09 AM
 */

#include "CWelcomeController.h"

void CWelcomeController::redraw() {
    clear();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    init_pair(2, COLOR_RED, COLOR_WHITE);
    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(1, 1, " WELCOME TO THE ULTIMATE SPREADSHEET EDITOR! ");
    attroff(A_BOLD | COLOR_PAIR(2));

    attrset(COLOR_PAIR(1));
    mvprintw(maxY - 1, 1, " F3 - go to the spreadsheet ");
    mvprintw(maxY - 1, 30, " F4 - exit ");
    attroff(COLOR_PAIR(1));

    refresh();
}

