/* 
 * File:   CExpressionParser.h
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 *
 * Created on June 7, 2015, 10:24 PM
 */

#ifndef CEXPRESSIONPARSER_H
#define	CEXPRESSIONPARSER_H

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <iterator>  
#include <queue>
#include <stack>
#include <sstream> 
#include <locale>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Class for parsing and evaluating mathematical expressions.
 * @details We use this class from CEquation to convert the expression
 * from the standart infix notation to reverse polish notation and then
 * to evaluate it. Supports +, -, *, /, %, ^, sin, cos, tan, exp, ln, log,
 * and constants e and PI.
 * 
 * @param input unparsed expression in infix notation
 * @return value of the expression
 */
class CExpressionParser {
public:
    /**
     * @brief Class constructor.
     * @details Saves the original expression.
     * 
     * @param input input unparsed expression in infix notation
     */
    CExpressionParser(const std::string& input);
    /**
     * @brief Check if there is no mis-match in parentheses
     * @details Compares the number of left parentheses to the number
     * of right parentheses.
     * 
     * @return true if there is no mi-match, false if there is a mis-match
     */
    bool MatchingParetheses();

    /**
     * @brief Deduce the numerical result from the RPN string passed to it.
     * @details http://en.wikipedia.org/wiki/Reverse_Polish_notation#Postfix_algorithm
     * 
     * @param rpn expression string converted to reverse polish notaion
     * @param result where to save the result as a string
     * 
     * @return true if there was no error, false if there was
     */
    bool Evaluate(const std::vector<std::string>& rpn, std::string& result);
    /**
     * @brief Convert given expression in infix format into reverse Polish notation.
     * 
     * @param inputs tokenized inputs
     * @return true if there was no error, false if there was
     */
    bool InfixToRPN(std::vector<std::string>& inputs);
private:
    std::string m_strInput;

    /**
     * @brief Replace all instances of selected string with replacement string.
     */
    void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
    /**
     * @brief Split selected text into delimited vector array of strings.
     */
    void Tokenize(std::list<std::string>& tokens, const std::string& delimiter);
};

const std::string charSet[] = {"(", ")", "%", "+", "-", "*", "/", "^", ","};

const double pi = 3.1415927;
const double e = 2.71828182846;

int Modulo(int num, int div);
unsigned int OpArgCount(const std::string& s);
int OpPrecedence(const std::string& s);
bool OpLeftAssoc(const std::string& s);
bool IsOperator(const std::string& s);
bool IsComma(const std::string& s);
std::string UpperCase(std::string input);
bool IsPi(const std::string& s);
bool IsE(const std::string& s);
bool IsFunction(const std::string& s);
bool IsFloat(const std::string& s);
bool IsNumber(const std::string& s);

#endif	/* CEXPRESSIONPARSER_H */

