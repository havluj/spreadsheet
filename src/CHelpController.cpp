/* 
 * File:   CHelpController.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 2:29 PM
 */

#include "CHelpController.h"

void CHelpController::redraw() {
    clear();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    const int SUBHELP = 6;

    attron(A_BOLD | A_UNDERLINE);
    mvprintw(0, 1, "NAVIGATING AROUND THE SPREADSHEET:");
    attroff(A_BOLD | A_UNDERLINE);
    mvprintw(1, SUBHELP, "E - edit / finish editing the expression");
    mvprintw(2, SUBHELP, "UP KEY - move one cell up");
    mvprintw(3, SUBHELP, "DOWN KEY - move one cell down");
    mvprintw(4, SUBHELP, "RIGHT KEY - move one cell right");
    mvprintw(5, SUBHELP, "LEFT KEY - move one cell left");

    attron(A_BOLD | A_UNDERLINE);
    mvprintw(7, 1, "EDITING THE EXPRESSION:");
    attroff(A_BOLD | A_UNDERLINE);
    mvprintw(8, SUBHELP, "If you want to input math expressions, make your first character is '='.");
    mvprintw(9, SUBHELP, "Otherwise, the input will be interpreted as a string.");
    mvprintw(10, SUBHELP, "Trying to compute with a string will lead to ERROR output.");
    mvprintw(11, SUBHELP, "For example: '= 150' is a number but '150' is a string.");
    mvprintw(12, SUBHELP, "To compute expressions, you can use these functions:");
    mvprintw(13, SUBHELP + 2, "avg(row,col:row,col) -> returns an average value of these cells");
    mvprintw(14, SUBHELP + 2, "sum(row,col:row,col) -> returns a sum of the values of these cells");
    mvprintw(15, SUBHELP + 2, "cell(row,col) -> returns a value of the cell");
    mvprintw(16, SUBHELP + 2, "sin(x), cos(x), tan(x)");
    mvprintw(17, SUBHELP + 2, "ln(x) -> natural logarithm (base e)");
    mvprintw(18, SUBHELP + 2, "log(x) -> logarithm with base 10");
    mvprintw(19, SUBHELP + 2, "sqrt(x) -> returns a square root of the value");
    mvprintw(20, SUBHELP + 2, "pow(x) == x^2");
    mvprintw(21, SUBHELP + 2, "exp(x) == e^x");
    mvprintw(22, SUBHELP + 2, "operators: +, -, *, /, %, ^");
    mvprintw(24, SUBHELP, "You can combine the expressions above however you like. For example:");
    mvprintw(25, SUBHELP + 2, "= ((sin(30) + 5) * 20) / avg(1,1:5,5)");

    attrset(COLOR_PAIR(1));
    mvprintw(maxY - 1, 1, " F3 - spreadsheet ");
    mvprintw(maxY - 1, 20, " F4 - exit ");
    attroff(COLOR_PAIR(1));

    refresh();
}
