/* 
 * File:   CText.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 12:02 AM
 */

#ifndef CTEXT_H
#define	CTEXT_H

#include <string>

#include "CCell.h"

/**
 * @brief Class representing a cell that can only display
 * a string.
 * @details This class is created when the input in the 
 * expression does not start with '='. We can not compute
 * with this cell.
 */
class CText : public CCell {
public:
    CText();
    CText(const CText& orig);
    virtual ~CText();
private:
};

#endif	/* CTEXT_H */

