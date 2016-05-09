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
/*
void GridFactory::initialiseWithNumberOfPieces(int numberOfPieces) {
    std::list<int> allValues;

    int totalGrids = pow(GRID_X*GRID_Y, numberOfPieces);
    for (int i=0; i < totalGrids; i++) {
        allValues.emplace_back(i);
    }
    
    if (_instance == NULL) {
        _instance = new GridFactory();
    }
    _instance->_freeIds = allValues;
}

Grid *GridFactory::createGrid(const std::list<Piece*> pieces) {
    if ((!_instance) || (_instance->_freeIds.size() == 0)) {
        return NULL;
    }
    
    Grid *toRet = NULL;
    do {
        toRet = Grid::createGridFromId(_instance->_freeIds.back(), pieces);
        _instance->_freeIds.pop_back();
    } while((toRet == NULL) && (_instance->_freeIds.size() != 0));
    
    return toRet;
}*/

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
    
    Grid *toRet = NULL;
    do {
        toRet = Grid::createGridFromId(_instance->_nextFreeId++, pieces);
    } while((toRet == NULL) && (_instance->_nextFreeId < (_instance->_totalGrids-1)));
    
    return toRet;
}