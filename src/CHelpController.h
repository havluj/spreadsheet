/* 
 * File:   CHelpController.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 2:29 PM
 */

#ifndef CHELPCONTROLLER_H
#define	CHELPCONTROLLER_H

#include <ncurses.h>

#include "CAbstractController.h"

/**
 * @brief Controller rendering help page to the user.
 * @details Control is passed to this controller by pressing 'F3'
 * on the keyboard while editing the spreadsheet. Job of this controller
 * is purely to render a help page to the user. 
 * It tells the user how to navigate around the spreadsheet and how to enter
 * and edit mathematical expressions in individual cells.
 */
class CHelpController : public CAbstractController {
public:
    virtual void redraw();
private:
};

#endif	/* CHELPCONTROLLER_H */

