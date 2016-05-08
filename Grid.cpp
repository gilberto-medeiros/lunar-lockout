//
//  Grid.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include "Grid.h"
#include <stdlib.h>
#include <iostream>

Grid::Grid(const std::list<Piece*> &pieces) : _pieces(pieces){
    memset(_grid, NULL, sizeof(GridDataType));
    
    GridPos pos;
    /*for (auto piece : _pieces) {
        do {
            pos.x = rand() % GRID_X;
            pos.y = rand() % GRID_Y;
        } while(pieceInPos(pos) != NULL);
        _grid[pos.x][pos.y] = piece;
        _piecePositions[piece] = pos;
    }*/
    
    // 4,1 0,0 0,4 1,3 3,2

    GridPos fixedPositions[5];
    fixedPositions[0].set(4,1);
    fixedPositions[1].set(0,4);
    fixedPositions[2].set(0,0);
    fixedPositions[3].set(1,3);
    fixedPositions[4].set(3,2);
    
    int i=0;
    for (auto piece : _pieces) {
        _grid[fixedPositions[i].x][fixedPositions[i].y] = piece;
        _piecePositions[piece] = fixedPositions[i++];
    }
}

Grid::Grid(const Grid &copyFrom) : _pieces(copyFrom._pieces), _piecePositions(copyFrom._piecePositions) {
    memcpy(_grid, copyFrom._grid, sizeof(GridDataType));
}

const std::list<Piece*> Grid::getPieces() const {
    return _pieces;
};

std::list<Grid*> Grid::computeAllMoves() const {
    std::list<Grid*> ret;
    for (auto piece : _pieces) {
        for ( int dirInt = UP; dirInt != COUNT; dirInt++ ) {
            Direction dir = static_cast<Direction>(dirInt);
            
            Grid *newGrid = piece->move(dir, this);
            if (newGrid != NULL) {
                ret.push_back(newGrid);
            }
        }
    }
    return ret;
}

GridPos Grid::positionOfPiece(Piece* piece) const {
    auto it = _piecePositions.find(piece);
    if (it != _piecePositions.end()) {
        return (*it).second;
    }
    return GridPos(0,0);
}

Piece* Grid::pieceInPos(GridPos &pos) const {
    return _grid[pos.x][pos.y];
}

void Grid::swapPieceToPos(Piece* piece, const GridPos &newPos) {
    GridPos startPos = positionOfPiece(piece);
    _grid[startPos.x][startPos.y] = NULL;
    _grid[newPos.x][newPos.y] = piece;
    _piecePositions[piece] = newPos;
}

void Grid::print() const {
    GridPos pos;
    for (int y=GRID_Y-1; y >=0 ; y--) {
        pos.y = y;
        for (int x=0; x < GRID_X; x++) {
            pos.x = x;
            Piece *p = pieceInPos(pos);
            std::string code = "+";
            if (p != NULL) {
                code = p->isSpecial() ? "S" : "O";
            }
            std::cout << code;
        }
        std::cout << std::endl;
    }
}

bool Grid::isSolution() {
    return _grid[2][2] != NULL && _grid[2][2]->isSpecial();
}
