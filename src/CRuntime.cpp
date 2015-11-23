/* 
 * File:   CRuntime.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 12:04 AM
 */

#include "CRuntime.h"

CRuntime::CRuntime() : m_currentView(-1) {
    m_controller = NULL;

    initscr();
    keypad(stdscr, TRUE);
    if (has_colors()) {
	  start_color();
    }
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    m_controllers.insert(std::make_pair((int) SPLASHSCREEN_VIEW, new CSplashscreenController()));
    m_controllers.insert(std::make_pair((int) WELCOME_VIEW, new CWelcomeController()));
    m_controllers.insert(std::make_pair((int) TABLE_VIEW, new CTableController()));
    m_controllers.insert(std::make_pair((int) HELP_VIEW, new CHelpController()));

    try {
	  changeView(WELCOME_VIEW);
    } catch (const std::invalid_argument& e) {
	  throw e;
    }
}

CRuntime::~CRuntime() {
    for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it) {
	  delete it->second;
    }

    endwin();
}

void CRuntime::run() {
    noecho();
    curs_set(0);

    int ch;
    int prevController = m_currentView;
    while (true) {
	  /* get the terminal dimensions */
	  getmaxyx(stdscr, m_terminalHeigth, m_terminalWidth);

	  /* make sure the terminal is large enough */
	  if (m_terminalWidth < 78 || m_terminalHeigth < 27) {
		if (m_currentView != SPLASHSCREEN_VIEW) {
		    prevController = m_currentView;
		}
		try {
		    changeView(SPLASHSCREEN_VIEW);
		} catch (const std::invalid_argument& e) {
		    throw e;
		}
	  } else {
		if (m_currentView == SPLASHSCREEN_VIEW) {
		    try {
			  changeView(prevController);
		    } catch (const std::invalid_argument& e) {
			  throw e;
		    }
		}
	  }

	  /* wait for a character to be pressed */
	  ch = getch();

	  switch (ch) {
		case KEY_F(4): // end the program
		    return;

		case KEY_RESIZE: // redraw the window
		    try {
			  changeView(m_currentView);
		    } catch (const std::invalid_argument& e) {
			  throw e;
		    }
		    break;

		case KEY_F(3): // show spreadsheet / help
		    if (m_currentView == TABLE_VIEW) {
			  try {
				changeView(HELP_VIEW);
			  } catch (const std::invalid_argument& e) {
				throw e;
			  }
		    } else {
			  try {
				changeView(TABLE_VIEW);
			  } catch (const std::invalid_argument& e) {
				throw e;
			  }
		    }
		    break;

		default:
		    m_controller->handleKey(ch);
		    break;
	  }
    }
}

void CRuntime::changeView(int view) {
    auto it = m_controllers.find(view);
    if (it == m_controllers.end()) {
	  throw std::invalid_argument("unknown view");
    }


    m_currentView = view;
    m_controller = m_controllers[view];

    m_controller->redraw();
}

