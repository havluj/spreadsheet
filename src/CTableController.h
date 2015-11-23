/* 
 * File:   CTableController.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 2:29 PM
 */

#ifndef CTABLECONTROLLER_H
#define	CTABLECONTROLLER_H

#include <string>
#include <ncurses.h>

#include "CAbstractController.h"
#include "CTable.h"
#include "CRuntime.h"

/**
 * @brief Controller that handles the actual spreadsheet editor.
 * @details The most important controller of all. This contoller
 * handles how to render the spreadsheet editor and the actual
 * logic how to navigate around the spreadsheet.
 */
class CTableController : public CAbstractController {
public:
    /**
     * @brief Controller's constructor.
     * @details Sets the m_rowPosition, m_colPosition,
     * m_rowStartingPosition, m_colStartingPosition to 0
     */
    CTableController();
    virtual ~CTableController();

    virtual void handleKey(int key);
    virtual void redraw();
private:
    /**
     * @brief Offset to the values rendered in header.
     * @details When the values (location, cell value, expression)
     * in the header are rendered, we use this offset as a x position 
     * where to render them.
     */
    static const int HEADER_VALUES_COLUMN = 11;

    /**
     * @brief A database of individual cells
     * @details We can ask this database to give us value of a
     * particular cell, or set a particular cell to a certain
     * expression. All the available methods are documented within the
     * CTable class.
     */
    CTable m_database;

    /**
     * @brief Current row position
     * @details In our editor, we have to remember our location. We 
     * store the row we are at in this variable.
     */
    int m_rowPosition;
    /**
     * @brief Current column position
     * @details In our editor, we have to remember our location. We 
     * store the column we are at in this variable.
     */
    int m_colPosition;
    /**
     * @brief From which row number do we start to render the table
     */
    int m_rowStartingPosition;
    /**
     * @brief From which column number do we start to render the table
     */
    int m_colStartingPosition;

    /**
     * @brief Renders the current location into the window's header.
     */
    void renderLocation() const;
    /**
     * @brief Renders the value of a cell we are currently on into the 
     * window's header.
     */
    void renderValue() const;
    /**
     * @brief Renders the expression of a cell we are currently on into the 
     * window's header.
     */
    void renderExpression() const;
    /**
     * @brief Renders the entire window's header
     * @details Renders the entire header also by calling renderLocation,
     * renderValue, and renderExpression functions.
     */
    void renderHeader() const;
    /**
     * @brief Renders the entire table
     * @details This method need to be called every time a cell is changed or
     * every time we change the location because we highlight our current
     * position in the table. Also, we need to make sure, our current location
     * is within the limits of the table we are drawing.
     */
    void renderTable();
    /**
     * @brief Renders the entire menu at the bottom of the page.
     */
    void renderMenu() const;

    /**
     * @brief Changes the current location in the table.
     * 
     * @param row Row we want to jump to.
     * @param col Column we want to jump to.
     */
    void changeLocation(int row, int col);
    /**
     * @brief Edit the expression of a cell we are currently working with (is on
     * our location).
     */
    void editExpression();
};

#endif	/* CTABLECONTROLLER_H */

