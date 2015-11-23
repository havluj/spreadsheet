/* 
 * File:   CTableController.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 2:29 PM
 */

#include "CTableController.h"

CTableController::CTableController() {
    m_colPosition = 1;
    m_rowPosition = 1;
    m_colStartingPosition = 1;
    m_rowStartingPosition = 1;
}

CTableController::~CTableController() {
}

void CTableController::handleKey(int key) {
    switch (key) {
	  case 'e':
	  case 'E':
		editExpression();
		break;

	  case KEY_DOWN:
		changeLocation(m_rowPosition + 1, m_colPosition);
		break;

	  case KEY_UP:
		changeLocation(m_rowPosition - 1, m_colPosition);
		break;

	  case KEY_RIGHT:
		changeLocation(m_rowPosition, m_colPosition + 1);
		break;

	  case KEY_LEFT:
		changeLocation(m_rowPosition, m_colPosition - 1);
		break;

	  default:
		break;
    }
}

void CTableController::redraw() {
    clear();

    renderHeader();
    renderTable();
    renderMenu();

    refresh();
}

void CTableController::renderLocation() const {
    move(0, HEADER_VALUES_COLUMN);
    clrtoeol();
    move(1, HEADER_VALUES_COLUMN + 2);
    clrtoeol();

    mvprintw(0, HEADER_VALUES_COLUMN, ": row    = %d", m_rowPosition);
    mvprintw(1, HEADER_VALUES_COLUMN + 2, "column = %d", m_colPosition);

    refresh();
}

void CTableController::renderValue() const {
    move(3, HEADER_VALUES_COLUMN);
    clrtoeol();

    mvprintw(3, HEADER_VALUES_COLUMN, ": %s",
		m_database.getValue(m_rowPosition, m_colPosition).c_str());

    refresh();
}

void CTableController::renderExpression() const {
    move(4, HEADER_VALUES_COLUMN);
    clrtoeol();

    mvprintw(4, HEADER_VALUES_COLUMN, ": %s",
		m_database.getExpression(m_rowPosition, m_colPosition).c_str());

    refresh();
}

void CTableController::renderHeader() const {
    attron(A_BOLD | A_UNDERLINE);
    mvprintw(0, 1, "Position");
    attroff(A_BOLD | A_UNDERLINE);
    renderLocation();

    attron(A_BOLD | A_UNDERLINE);
    mvprintw(3, 1, "Cell Value");
    attroff(A_BOLD | A_UNDERLINE);
    renderValue();

    attron(A_BOLD | A_UNDERLINE);
    mvprintw(4, 1, "Expression");
    attroff(A_BOLD | A_UNDERLINE);
    renderExpression();

    refresh();
}

void CTableController::renderTable() {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    int rowsCnt = (maxY - 10 - 3) / 2;
    if ((rowsCnt + m_rowStartingPosition) < m_rowPosition) {
	  m_rowStartingPosition = m_rowPosition - rowsCnt;
    } else if (m_rowPosition < m_rowStartingPosition) {
	  m_rowStartingPosition = m_rowPosition;
    }

    int colsCnt = (maxX - 6) / 10;
    if ((colsCnt + m_colStartingPosition) <= m_colPosition) {
	  m_colStartingPosition = m_colPosition - colsCnt + 1;
    } else if (m_colPosition < m_colStartingPosition) {
	  m_colStartingPosition = m_colPosition;
    }

    //==========================================================================
    /* create the grid */
    //==========================================================================
    attrset(COLOR_PAIR(3));
    /* horizontal lines */
    int offset = 10;
    for (int i = m_rowStartingPosition; i < (rowsCnt + m_rowStartingPosition); i++) {
	  if (m_rowPosition == i || m_rowPosition == (i + 1)) {
		attrset(COLOR_PAIR(2));
	  }
	  move(offset, 0);
	  hline(0, maxX);
	  attroff(COLOR_PAIR(2));
	  attrset(COLOR_PAIR(3));
	  offset += 2;
    }

    /* vertical lines */
    offset = 5;
    for (int i = m_colStartingPosition; i <= (colsCnt + m_colStartingPosition); i++) {
	  if (m_colPosition == i || m_colPosition == (i - 1)) {
		attrset(COLOR_PAIR(2));
	  }
	  move(7, offset);
	  vline(0, maxY - 7 - 3);
	  attroff(COLOR_PAIR(2));
	  attrset(COLOR_PAIR(3));
	  offset += 10;
    }
    attroff(COLOR_PAIR(3));

    /* We need to draw the main lines after we draw the regular ones, so they
	 will appear to be in front of the regular ones. */
    /* Main vertical line */
    move(7, 4);
    vline(0, maxY - 7 - 3);

    /* Main horizontal line. */
    move(8, 0);
    hline('=', maxX);

    //==========================================================================
    /* numbering cols and rows */
    //==========================================================================
    /* rows */
    offset = 9;
    for (int i = m_rowStartingPosition; i <= (rowsCnt + m_rowStartingPosition); i++) {
	  if (m_rowPosition == i) {
		attrset(COLOR_PAIR(2));
	  }
	  mvprintw(offset, 0, "%4d", i);
	  attroff(COLOR_PAIR(2));
	  offset += 2;
    }

    /* columns */
    offset = 6;
    std::string s;
    int digitsCnt;
    for (int i = m_colStartingPosition; i <= (colsCnt + m_colStartingPosition); i++) {
	  /* center the numbers */
	  s = "";
	  digitsCnt = std::to_string(i).length();
	  for (int j = 0; j < ((9 - digitsCnt) / 2); j++) {
		s.append(" ");
	  }
	  s.append(std::to_string(i));
	  for (int j = (s.length()); j < 9; j++) {
		s.append(" ");
	  }

	  if (m_colPosition == i) {
		attrset(COLOR_PAIR(2));
	  }
	  /* make sure to display only a part if there is not enough space */
	  if ((int) s.length() > (maxX - offset)) {
		mvprintw(7, offset, "%.*s", (maxX - offset), s.c_str());
	  } else {
		mvprintw(7, offset, "%s", s.c_str());
	  }
	  attroff(COLOR_PAIR(2));
	  offset += 10;
    }

    //==========================================================================
    /* filling out the table */
    //==========================================================================
    int rowOffset = 9;
    for (int i = m_rowStartingPosition; i <= (rowsCnt + m_rowStartingPosition); i++) {
	  int colOffset = 6;
	  for (int j = m_colStartingPosition; j <= (colsCnt + m_colStartingPosition); j++) {
		/* center the content */
		s = "";
		digitsCnt = m_database.getValue(i, j).length();
		for (int k = 0; k < ((9 - digitsCnt) / 2); k++) {
		    s.append(" ");
		}
		s.append(m_database.getValue(i, j));
		for (int k = (s.length()); k < 9; k++) {
		    s.append(" ");
		}

		/* keep only 9 characters */
		if (s.length() > 9) {
		    s = s.substr(0, 6);
		    s.append("...");
		}

		if (m_colPosition == j && m_rowPosition == i) {
		    attrset(COLOR_PAIR(2));
		}
		/* make sure to display only a part if there is not enough space */
		if ((int) s.length() > (maxX - colOffset)) {
		    mvprintw(rowOffset, colOffset, "%.*s", (maxX - colOffset), s.c_str());
		} else {
		    mvprintw(rowOffset, colOffset, "%s", s.c_str());
		}
		attroff(COLOR_PAIR(2));
		colOffset += 10;
	  }
	  rowOffset += 2;
    }

    refresh();
}

void CTableController::renderMenu() const {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    attrset(COLOR_PAIR(1));
    mvprintw(maxY - 1, 1, " E - edit the expression ");
    mvprintw(maxY - 1, 27, " F3 - help ");
    mvprintw(maxY - 1, 39, " F4 - exit ");
    attroff(COLOR_PAIR(1));

    refresh();
}

void CTableController::changeLocation(int row, int col) {
    if (row < 1 || col < 1) {
	  return;
    } else {
	  m_rowPosition = row;
	  m_colPosition = col;

	  renderLocation();
	  renderValue();
	  renderExpression();
	  renderTable();
    }
}

void CTableController::editExpression() {
    echo();
    curs_set(1);

    move(4, HEADER_VALUES_COLUMN + 2);
    clrtoeol();

    char str[66];

    move(4, HEADER_VALUES_COLUMN + 2);
    // push already existing expression into the buffer
    std::string expression = m_database.getExpression(m_rowPosition, m_colPosition);
    for (int i = ((int) expression.length() - 1); i >= 0; i--) {
	  ungetch(expression.at(i));
    }
    getnstr(str, 65);

    expression = str;
    m_database.updateElement(m_rowPosition, m_colPosition, expression);

    noecho();
    curs_set(0);

    renderValue();
    renderTable();
}