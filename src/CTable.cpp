/* 
 * File:   CTable.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 12:02 AM
 */

#include "CTable.h"

CTable::CTable() {
    m_idCounter = 0;
}

CTable::~CTable() {
    for (auto it = m_database.begin(); it != m_database.end(); ++it) {
	  delete it->second;
    }
}

void CTable::reCompute(int row, int col) {
    auto it = m_database.find(std::make_pair(row, col));
    if (it != m_database.end()) {
	  it->second->reCompute();
    }
}

void CTable::updateElement(int row, int col, std::string value) {
    std::set<std::pair<int, int>> affectedBy;

    auto it = m_database.find(std::make_pair(row, col));
    if (it == m_database.end()) {
	  CCell* newCell;
	  if (value.length() > 0 && value.at(0) == '=') {
		newCell = new CEquation(this);
	  } else {
		newCell = new CText();
	  }
	  newCell->setId(m_idCounter++);
	  m_database.insert(std::make_pair(std::make_pair(row, col), newCell));
	  affectedBy = newCell->update(value);
    } else {
	  delete it->second;

	  CCell* newCell;
	  if (value.length() > 0 && value.at(0) == '=') {
		newCell = new CEquation(this);
	  } else {
		newCell = new CText();
	  }
	  newCell->setId(m_idCounter++);
	  m_database[std::make_pair(row, col)] = newCell;
	  affectedBy = newCell->update(value);
    }

    // create the affecting relationships
    if (affectedBy.size() > 0) {
	  for (auto i = affectedBy.begin(); i != affectedBy.end(); ++i) {
		auto relIt = m_relationships.find(*i);
		if (relIt == m_relationships.end()) {
		    /* create new entry */
		    std::set<std::pair<int, int>> tmp;
		    tmp.insert(std::make_pair(row, col));
		    m_relationships.insert(std::make_pair(std::make_pair(i->first, i->second), tmp));
		} else {
		    /* expand the set */
		    relIt->second.insert(std::make_pair(row, col));
		}
	  }
    }

    auto recalcIt = m_relationships.find(std::make_pair(row, col));
    if (recalcIt != m_relationships.end()) {
	  for (auto i = recalcIt->second.begin(); i != recalcIt->second.end(); ++i) {
		reCompute((*i).first, (*i).second);
	  }
    }
}

std::string CTable::getValue(int row, int col) const {
    std::string returnValue;

    auto it = m_database.find(std::make_pair(row, col));
    if (it != m_database.end()) {
	  returnValue = it->second->getValueAsString();
    }

    return returnValue;
}

CCell * CTable::getCell(int row, int col) const {
    std::string returnValue;

    auto it = m_database.find(std::make_pair(row, col));
    if (it != m_database.end()) {
	  return it->second;
    } else {
	  throw std::logic_error("ERR: empty cell");
    }
}

std::string CTable::getExpression(int row, int col) const {
    std::string returnValue;

    auto it = m_database.find(std::make_pair(row, col));
    if (it != m_database.end()) {
	  returnValue = it->second->getExpression();
    }

    return returnValue;
}