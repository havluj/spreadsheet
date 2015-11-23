/* 
 * File:   main.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 1, 2015, 10:03 AM
 */

 /**
  * @mainpage Spreadsheet editor
  * @author Jan Havlůj
  * 
  * A simple spreadsheet editor using NCurses.\n
  * This editor supports mathematical expressions using these functions:\n
  * sin, cos, tan, log, ln, exp\n
  * and these symbols:\n
  * *, /, +, -, %\n
  * \n
  * You can also refer to the values of other cells using these functions:\n
  * sum, avg, cell\n
  * \n
  * You can find more info on how to use the program inside the program's help page.
  */

#include "CRuntime.h"

int main(int argc, char** argv) {
    CRuntime app;
    app.run();

    return 0;
}

