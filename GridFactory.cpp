//
//  GridFactory.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 09/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include "GridFactory.h"
#include "Common.h"
#include "Grid.h"
#include <math.h>

GridFactory *GridFactory::_instance = NULL;


void GridFactory::initialiseWithNumberOfPieces(int numberOfPieces) {
    if (_instance == NULL) {
        _instance = new GridFactory();
    }
    _instance->_nextFreeId = 0;
    _instance->_totalGrids = pow(GRID_X*GRID_Y, numberOfPieces);
}

Grid *GridFactory::createGrid(const std::list<Piece*> pieces) {
    if ((!_instance) || (_instance->_nextFreeId >= (_instance->_totalGrids-1))) {
        return NULL;
    }
    
    Analytics::startTimer("create valid grid");
    Grid *toRet = NULL;
    do {
        toRet = Grid::createGridFromId(_instance->_nextFreeId++, pieces);
    } while((toRet == NULL) && (_instance->_nextFreeId < (_instance->_totalGrids-1)));
    
    Analytics::endTimer("create valid grid");
    return toRet;
}