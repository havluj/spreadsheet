/* 
 * File:   SplashscreenController.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 5, 2015, 1:46 AM
 */

#ifndef CSPLASHSCREENCONTROLLER_H
#define	CSPLASHSCREENCONTROLLER_H

#include <ncurses.h>

#include "CAbstractController.h"

/**
 * @brief Controller handling window size
 * @details If the window where the program is running in is too small,
 * this controller is called. Its job is to inform the user, that his
 * terminal window is to small and that he should resize it. Once the 
 * terminal window is large enough, user is swiched back to the controller
 * he was on before being redirected to this controller.
 */
class CSplashscreenController : public CAbstractController {
public:
    virtual void redraw();
private:
};

#endif	/* CSPLASHSCREENCONTROLLER_H */

