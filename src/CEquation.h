/* 
 * File:   CEquation.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 4, 2015, 12:03 AM
 */

#ifndef CEQUATION_H
#define	CEQUATION_H

#include <sstream> 
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <map>  
#include <string>  
#include <vector>  
#include <iterator>   

#include "CCell.h"
#include "CExpressionParser.h"
#include "CTable.h"

class CTable;

class CEquation : public CCell {
public:
    CEquation(const CTable* table);
    CEquation(const CEquation& orig);
    virtual ~CEquation();

    virtual std::set<std::pair<int, int>> update(std::string exp);
    virtual void reCompute();

    virtual double getValue() const;
    virtual std::string getValueAsString() const;
private:
    const int LEFT_ASSOC = 0;
    const int RIGHT_ASSOC = 1;

    const CTable* m_database;

    std::vector<std::string> m_rpn;

    bool m_error;
    std::string m_errorMsg;
    double m_value;

    std::set<std::pair<int, int>> m_affectedBy;

    double string_to_double(const std::string& s);
    std::string replaceOtherCells(std::string exp);
    void compute();
};
#endif	/* CEQUATION_H */

