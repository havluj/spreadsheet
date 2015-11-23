/* 
 * File:   CAbstractController.cpp
 * Author: Jan Havlůj {@literal <jan@havluj.eu>}
 * 
 * Created on June 4, 2015, 2:28 PM
 */

#include "CAbstractController.h"

CAbstractController::~CAbstractController() {
}

void CAbstractController::handleKey(int key) {
}

void CAbstractController::redraw() {
    clear();
}
