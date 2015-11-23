/* 
 * File:   CRuntime.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 12:04 AM
 */

#ifndef CRUNTIME_H
#define	CRUNTIME_H

#include <map>
#include <ncurses.h>

#include "CAbstractController.h"
#include "CTableController.h"
#include "CHelpController.h"
#include "CSplashscreenController.h"
#include "CWelcomeController.h"

/**
 * @brief Class where the main cycle of the program runs.
 * @details This class handles which contoller are we using, listens
 * for key strokes and handles them.
 */
class CRuntime {
public:
    static const int SPLASHSCREEN_VIEW = 0;
    static const int WELCOME_VIEW = 1;
    static const int TABLE_VIEW = 2;
    static const int HELP_VIEW = 3;

    /**
     * @brief Class constructor.
     * @details Enables and configures NCurses. Sets default values to the
     * private variables.
     */
    CRuntime();
    /**
     * @brief Copy constructor.
     * 
     * @param src original runtime
     */
    CRuntime(const CRuntime& src) = delete;
    /**
     * @brief Class destructor.
     * @details Deletes all the allocated memory.
     */
    virtual ~CRuntime();

    /**
     * @brief Main cycle of the program.
     * @details Handles the keystrokes and manages which controller we
     * are using.
     */
    void run();
    /**
     * @brief Changes the current view.
     * @details Changes the current controller and calls contoller's methods
     * to redraw the screen.
     * 
     * @param view one of the constants (SPLASHSCREEN_VIEW, WELCOME_VIEW, 
     * TABLE_VIEW, HELP_VIEW)
     */
    void changeView(int view);
private:
    std::map<int, CAbstractController*> m_controllers;

    int m_currentView;
    CAbstractController* m_controller;

    int m_terminalWidth;
    int m_terminalHeigth;
};

#endif	/* CRUNTIME_H */

