//
//  Piece.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include "Piece.h"
#include "Grid.h"
#include "GridPos.h"
#include "IdCache.h"
#include "GridFactory.h"
#include <iostream>

Piece::Piece(bool isSpecial, int idBase) : _isSpecial(isSpecial), _idBase(idBase){
    
}

bool Piece::isSpecial() const {
    return _isSpecial;
}

bool moveInDirection(GridPos &pos, const GridPos &direction) {
    pos += direction;
    Analytics::reportEvent("move Calculation");
    
    return pos.x >=0 && pos.x < GRID_X && pos.y >=0 && pos.y < GRID_Y;
}

Grid* Piece::move(Direction dir, const Grid* inGrid) {
    Analytics::startTimer("piece move");
    const GridPos& directionVec = directionToVec(dir);
    GridPos piecePos = inGrid->positionOfPiece(this);
    GridPos oldPos(piecePos);
    
    bool movePossible = false;
    while(moveInDirection(piecePos, directionVec)){
        Piece *adjacent = inGrid->pieceInPos(piecePos);
        if (adjacent) {
            if (!movePossible) {
                Analytics::endTimer("piece move");
                return NULL;
            }
            
            Grid *newGrid = new Grid(*inGrid);
            newGrid->swapPieceToPos(this, oldPos);
            
            if (IdCache::reserveId(newGrid->calculateId())) {
                Analytics::reportEvent("Grid pushed");
                newGrid->addMove(dir, this);
                Analytics::endTimer("piece move");
                return newGrid;
            }
            else {
                Analytics::reportEvent("Grid dropped (cached)");
                // this grid was already explored in the past
                delete newGrid;
                Analytics::endTimer("piece move");
                return NULL;
            }
        }
        // many coppies here
        oldPos = piecePos;
        movePossible = true;
    }
    
    Analytics::endTimer("piece move");
    return NULL;
}