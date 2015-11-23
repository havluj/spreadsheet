/* 
 * File:   CCell.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 12:02 AM
 */

#ifndef CCELL_H
#define	CCELL_H

#include <string>
#include <set>
#include <stdexcept>

/**
 * @brief Class representing an abstract cell.
 * @details Future cells are supposed to extend this class. This class
 * provides an interface of what the inhereted classes need to implement.
 */
class CCell {
public:
    CCell();
    /**
     * @brief Copy constructor.
     * 
     * @param orig Original cell.
     */
    CCell(const CCell& orig);
    virtual ~CCell();

    /**
     * @brief Updates the cell's contents
     * @details Updates the cell's contents and if that expression is a
     * mathematical expression, it calculates it immidiatelly. If there
     * are any functions, that need other cells to work (cell(), sum(), 
     * avg()) a relationship table is created and then returned.
     * 
     * @param exp Expression that we need to parse
     * @return A set of cells that affect this cell
     */
    virtual std::set<std::pair<int, int>> update(std::string exp);
    /**
     * @brief Recalculates the cell using the current, unchanged,
     * expression.
     * @details This method is usually called when a cell that is affecting
     * this cell is changed.
     */
    virtual void reCompute();

    /**
     * @brief Return's the value of this cell as a double.
     * @details Works only, if the cell is a math expression, not a string
     * of text.
     * 
     * @return value of this cell
     */
    virtual double getValue() const;
    /**
     * @brief Return's the value of this cell as a double.
     * 
     * @return value of this cell
     */
    virtual std::string getValueAsString() const;
    /**
     * @brief Return's the expression of this cell.
     * 
     * @return expression as a string
     */
    virtual std::string getExpression() const;

    /**
     * @brief Return's the id of this cell.
     * @return id
     */
    unsigned int getId() const;
    /**
     * @brief Sets the id of this cell.
     * 
     * @param int id
     */
    void setId(unsigned int id);
protected:
    std::string m_expression;

    unsigned int m_id;
};

#endif	/* CCELL_H */

