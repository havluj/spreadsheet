/* 
 * File:   CWelcomeController.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 5, 2015, 2:09 AM
 */

#ifndef CWELCOMECONTROLLER_H
#define	CWELCOMECONTROLLER_H

#include <ncurses.h>

#include "CAbstractController.h"

/**
 * @brief Welcome screen.
 * @details The first screen you see when you open the program.
 * It welcomes the user and lets him quit the program or enter the
 * spreadsheet editor.
 */
class CWelcomeController : public CAbstractController {
public:
    virtual void redraw();
private:
};

#endif	/* CWELCOMECONTROLLER_H */

