/* 
 * File:   CTable.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 12:02 AM
 */

#ifndef CTABLE_H
#define	CTABLE_H

#include <map>
#include <string>
#include <stdexcept>

#include "CCell.h"
#include "CText.h"
#include "CEquation.h"

/**
 * @brief Class that represents a database of individual cells.
 * @details This class is used as a database storage of all the cells in the
 * spreadsheet. We can ask the database for a cell's value, expression, etc.
 * We also query this database to create and edit cells.
 */
class CTable {
public:
    /**
     * @brief Class constructor.
     * @details Sets the private variables to default values.
     */
    CTable();
    /**
     * @brief Copy constructor.
     * 
     * @param orig original CTable
     */
    CTable(const CTable& orig) = delete;
    /**
     * @brief Class destructor.
     * @details Frees all the allocated memory.
     */
    virtual ~CTable();

    /**
     * @brief Re-evaluate a particular cell.
     * @details Asks a cell to evaluate itself again. We use this method mainly
     * when a particular cell is dependant on a different cell, which has just
     * been changed.
     * 
     * @param row cell on what row
     * @param col cell on what column
     */
    virtual void reCompute(int row, int col);
    /**
     * @brief Update cell's expression.
     * @details Asks the database to update cell's expression or creates a new cell
     * with this expression. Then the cell is asked to evaluate itself and that 
     * proccess returns locations of cells that affect this cells. Then a
     * relationship table if formed. Next time, when a cell that affects a different
     * cell is changed, method reCompute is called on the affected cell.
     * 
     * @param row cell on what row
     * @param col cell on what column
     * @param value new expression
     */
    virtual void updateElement(int row, int col, std::string value);

    /**
     * @brief Returns the cell's expression.
     * 
     * @param row cell on what row
     * @param col cell on what column
     * 
     * @return expression as a string
     */
    virtual std::string getExpression(int row, int col) const;
    /**
     * @brief Returns the cell's value.
     * 
     * @param row cell on what row
     * @param col cell on what column
     * 
     * @return cell's value as a string
     */
    virtual std::string getValue(int row, int col) const;
    /**
     * @brief Returns a pointer to a particular cell.
     * 
     * @param row cell on what row
     * @param col cell on what column
     * 
     * @return a pointer to the cell
     */
    virtual CCell* getCell(int row, int col) const;
private:
    std::map<std::pair<int, int>, std::set<std::pair<int, int>>> m_relationships;
    std::map<std::pair<int, int>, CCell*> m_database;
    unsigned int m_idCounter;
};

#endif	/* CTABLE_H */

