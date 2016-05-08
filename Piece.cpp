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

Piece::Piece(bool isSpecial) : _isSpecial(isSpecial){
    
}

bool Piece::isSpecial() const {
    return _isSpecial;
}

bool moveInDirection(GridPos &pos, const GridPos &direction) {
    pos = pos + direction;
    
    return pos.x >=0 && pos.x < GRID_X && pos.y >=0 && pos.y < GRID_X;
}

Grid* Piece::move(Direction dir, const Grid* inGrid) {
    const GridPos& directionVec = directionToVec(dir);
    GridPos piecePos = inGrid->positionOfPiece(this);
    GridPos oldPos(piecePos);
    
    bool movePossible = false;
    while(moveInDirection(piecePos, directionVec)){
        Piece *adjacent = inGrid->pieceInPos(piecePos);
        if (adjacent) {
            if (!movePossible) {
                return NULL;
            }
            // ugly
            Grid *newGrid = new Grid(*inGrid);
            newGrid->swapPieceToPos(this, oldPos);
            return newGrid;
        }
        // many coppies here
        oldPos = piecePos;
        movePossible = true;
    }
    
    return NULL;
}