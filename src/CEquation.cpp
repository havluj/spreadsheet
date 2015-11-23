/* 
 * File:   CEquation.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 12:03 AM
 */

#include "CEquation.h"

CEquation::CEquation(const CTable* table) {
    m_database = table;
    m_error = false;
}

CEquation::CEquation(const CEquation& orig) {
    m_error = false;
    m_expression = orig.m_expression;
}

CEquation::~CEquation() {
}

std::set<std::pair<int, int>> CEquation::update(std::string exp) {
    m_error = false;

    m_affectedBy.clear();
    m_expression = exp;

    compute();

    return m_affectedBy;
}

void CEquation::reCompute() {
    m_error = false;
    compute();
}

double CEquation::getValue() const {
    if (m_error) {
	  throw std::logic_error(m_errorMsg);
    } else {
	  return m_value;
    }
}

std::string CEquation::getValueAsString() const {
    if (m_error) {
	  return m_errorMsg;
    } else {
	  std::ostringstream out;
	  out << std::setprecision(3) << m_value;
	  return out.str();
    }
}

double CEquation::string_to_double(const std::string& s) {
    std::istringstream i(s);
    double x;
    if (!(i >> x))
	  return 0;
    return x;
}

std::string CEquation::replaceOtherCells(std::string exp) {
    // erase all the spaces
    exp.erase(std::remove(exp.begin(), exp.end(), ' '), exp.end());
    m_expression = exp; 
    // replace = with a space
    exp.replace(exp.find("="), 1, " "); 
    // erase all the spaces
    exp.erase(std::remove(exp.begin(), exp.end(), ' '), exp.end());
    

    /* make everything upper case */
    exp = UpperCase(exp);

    /* PARSING CELL FUNCTION */
    std::string phraze = "CELL"; // substring we are looking for
    std::string subExp;
    size_t pos = exp.find(phraze, 0);
    while (pos != std::string::npos) {
	  size_t endingParentheses = exp.find(")", pos);
	  subExp = exp.substr(pos + 4, endingParentheses - pos + 1);
	  std::stringstream stream;
	  stream << subExp;
	  char ch;
	  stream >> ch;
	  if (ch != '(') {
		m_error = true;
		m_errorMsg = "ERR: wrong CELL format";
		return exp;
	  }
	  int row = 0, col = 0;
	  stream >> row;
	  stream >> ch;
	  if (ch != ',') {
		m_error = true;
		m_errorMsg = "ERR: wrong CELL format";
		return exp;
	  }
	  stream >> col;

	  stream >> ch;
	  if (ch != ')') {
		m_error = true;
		m_errorMsg = "ERR: wrong CELL format";
		return exp;
	  }

	  if (col == 0 || row == 0) {
		m_error = true;
		m_errorMsg = "ERR: wrong CELL format";
		return exp;
	  }

	  m_affectedBy.insert(std::make_pair(row, col));

	  //replace the cell
	  double val = 0;
	  CCell* cell = NULL;
	  try {
		cell = m_database->getCell(row, col);
		if (cell->getId() == m_id) {
		    m_error = true;
		    m_errorMsg = "ERR: trying to get value of itself in CELL function";
		    return exp;
		} else {
		    val = cell->getValue();
		}
	  } catch (std::logic_error e) {
		m_error = true;
		m_errorMsg = "ERR: trying to compute with string or empty cell";
		return exp;
	  }

	  exp.replace(pos, endingParentheses - pos + 1, std::to_string(val));

	  pos = exp.find(phraze, pos + 1);
    }


    /* PARSING SUM FUNCTION */
    phraze = "SUM"; // substring we are looking for
    pos = exp.find(phraze, 0);
    while (pos != std::string::npos) {
	  size_t endingParentheses = exp.find(")", pos);
	  subExp = exp.substr(pos + 3, endingParentheses - pos + 1);
	  std::stringstream stream;
	  stream << subExp;
	  char ch;
	  stream >> ch;
	  if (ch != '(') {
		m_error = true;
		m_errorMsg = "ERR: wrong SUM format";
		return exp;
	  }
	  int rowBegin = 0, colBegin = 0, rowEnd = 0, colEnd = 0;
	  stream >> rowBegin;
	  stream >> ch;
	  if (ch != ',') {
		m_error = true;
		m_errorMsg = "ERR: wrong SUM format";
		return exp;
	  }
	  stream >> colBegin;

	  stream >> ch;
	  if (ch != ':') {
		m_error = true;
		m_errorMsg = "ERR: wrong SUM format";
		return exp;
	  }
	  stream >> rowEnd;
	  stream >> ch;
	  if (ch != ',') {
		m_error = true;
		m_errorMsg = "ERR: wrong SUM format";
		return exp;
	  }
	  stream >> colEnd;

	  stream >> ch;
	  if (ch != ')') {
		m_error = true;
		m_errorMsg = "ERR: wrong SUM format";
		return exp;
	  }

	  if (colBegin == 0 || rowBegin == 0 || rowEnd == 0 || colEnd == 0) {
		m_error = true;
		m_errorMsg = "ERR: wrong SUM format";
		return exp;
	  }

	  if (rowBegin > rowEnd) {
		int tmp = rowEnd;
		rowEnd = rowBegin;
		rowBegin = tmp;
	  }

	  if (colBegin > colEnd) {
		int tmp = colEnd;
		colEnd = colBegin;
		colBegin = tmp;
	  }

	  double val = 0;
	  for (int i = rowBegin; i <= rowEnd; i++) {
		for (int j = colBegin; j <= colEnd; j++) {
		    m_affectedBy.insert(std::make_pair(i, j));

		    //replace the cell
		    CCell* cell = NULL;
		    try {
			  cell = m_database->getCell(i, j);
			  if (cell->getId() == m_id) {
				m_error = true;
				m_errorMsg = "ERR: trying to get value of itself in SUM function";
			  } else {
				val += cell->getValue();
			  }
		    } catch (std::logic_error e) {
			  m_error = true;
			  m_errorMsg = "ERR: trying to compute with string or empty cell";
		    }
		}
	  }
	  if (m_error) {
		return exp;
	  }

	  exp.replace(pos, endingParentheses - pos + 1, std::to_string(val));

	  pos = exp.find(phraze, pos + 1);
    }


    /* PARSING SUM FUNCTION */
    phraze = "AVG"; // substring we are looking for
    pos = exp.find(phraze, 0);
    while (pos != std::string::npos) {
	  size_t endingParentheses = exp.find(")", pos);
	  subExp = exp.substr(pos + 3, endingParentheses - pos + 1);
	  std::stringstream stream;
	  stream << subExp;
	  char ch;
	  stream >> ch;
	  if (ch != '(') {
		m_error = true;
		m_errorMsg = "ERR: wrong AVG format";
		return exp;
	  }
	  int rowBegin = 0, colBegin = 0, rowEnd = 0, colEnd = 0;
	  stream >> rowBegin;
	  stream >> ch;
	  if (ch != ',') {
		m_error = true;
		m_errorMsg = "ERR: wrong AVG format";
		return exp;
	  }
	  stream >> colBegin;

	  stream >> ch;
	  if (ch != ':') {
		m_error = true;
		m_errorMsg = "ERR: wrong AVG format";
		return exp;
	  }
	  stream >> rowEnd;
	  stream >> ch;
	  if (ch != ',') {
		m_error = true;
		m_errorMsg = "ERR: wrong AVG format";
		return exp;
	  }
	  stream >> colEnd;

	  stream >> ch;
	  if (ch != ')') {
		m_error = true;
		m_errorMsg = "ERR: wrong AVG format";
		return exp;
	  }

	  if (colBegin == 0 || rowBegin == 0 || rowEnd == 0 || colEnd == 0) {
		m_error = true;
		m_errorMsg = "ERR: wrong AVG format";
		return exp;
	  }

	  if (rowBegin > rowEnd) {
		int tmp = rowEnd;
		rowEnd = rowBegin;
		rowBegin = tmp;
	  }

	  if (colBegin > colEnd) {
		int tmp = colEnd;
		colEnd = colBegin;
		colBegin = tmp;
	  }

	  double val = 0;
	  for (int i = rowBegin; i <= rowEnd; i++) {
		for (int j = colBegin; j <= colEnd; j++) {
		    m_affectedBy.insert(std::make_pair(i, j));

		    //replace the cell
		    CCell* cell = NULL;
		    try {
			  cell = m_database->getCell(i, j);
			  if (cell->getId() == m_id) {
				m_error = true;
				m_errorMsg = "ERR: trying to get value of itself in AVG function";
			  } else {
				val += cell->getValue();
			  }
		    } catch (std::logic_error e) {
			  m_error = true;
			  m_errorMsg = "ERR: trying to compute with string or empty cell";
		    }
		}
	  }
	  if (m_error) {
		return exp;
	  }
	  int rowCnt = rowEnd - rowBegin + 1;
	  int colCnt = colEnd - colBegin + 1;

	  exp.replace(pos, endingParentheses - pos + 1, std::to_string(val / (rowCnt * colCnt)));

	  pos = exp.find(phraze, pos + 1);
    }

    return exp;
}

void CEquation::compute() {
    std::string s = replaceOtherCells(m_expression);
    if (!m_error) {
	  CExpressionParser parser(s);

	  if (!parser.MatchingParetheses()) {
		m_error = true;
		m_errorMsg = "ERR: mismatched parentheses or empty input";
	  } else {
		std::vector<std::string> RPN;

		if (parser.InfixToRPN(RPN)) {
		    std::string str_result;
		    if (parser.Evaluate(RPN, str_result)) {
			  m_value = string_to_double(str_result);
		    }
		} else {
		    m_error = true;
		    m_errorMsg = "ERR: mismatched parentheses";
		}
	  }
    }
}