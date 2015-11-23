/* 
 * File:   CText.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 12:02 AM
 */

#include "CText.h"

CText::CText() {
}

CText::CText(const CText& orig) {
    m_expression = orig.m_expression;
}

CText::~CText() {
}

