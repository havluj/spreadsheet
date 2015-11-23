/* 
 * File:   CAbstractController.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 2:28 PM
 */

#ifndef CABSTRACTCONTROLLER_H
#define	CABSTRACTCONTROLLER_H

#include <ncurses.h>

/**
 * @brief Abstract controller to be inhereted from.
 * @details Each "page", meaning part of the application, is supposed to have
 * its own controller, which should be extending this abstract controller.
 * Each controller needs to be handle keystrokes, that are passed from 
 * CRuntime and should be able to redraw the entire window.
 */
class CAbstractController {
public:
    /**
     * @brief Class destructor.
     * @details Class destructor. Does nothing.
     */
    virtual ~CAbstractController();

    /**
     * @brief Handles key strokes.
     * @details The program reads key strokes in the main cycle and if they are 
     * not handled there, they are passed to this method of the current 
     * controller. 
     * 
     * @param key Key pressed
     */
    virtual void handleKey(int key);

    /**
     * @brief Drawing on the current window.
     * @details Each time this method is called, the current windows needs
     * to be cleared and then we can render any information on the screen using 
     * this method.
     */
    virtual void redraw();
private:
};

#endif	/* CABSTRACTCONTROLLER_H */

