/* 
 * File:   CCell.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 12:02 AM
 */

#include "CCell.h"

CCell::CCell() {
}

CCell::CCell(const CCell& orig) {
    m_expression = orig.m_expression;
}

CCell::~CCell() {
}

std::set<std::pair<int, int>> CCell::update(std::string exp) {
    std::set<std::pair<int, int>> affectedBy;

    m_expression = exp;

    return affectedBy;
}

void CCell::reCompute() {
}

double CCell::getValue() const {
    throw std::logic_error("ERR: can't compute with a string");
}

std::string CCell::getValueAsString() const {
    return m_expression;
}

std::string CCell::getExpression() const {
    return m_expression;
}

unsigned int CCell::getId() const {
    return m_id;
}

void CCell::setId(unsigned int id) {
    m_id = id;
}