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
#include <sstream>
#include <math.h>
#include "IdCache.h"

void Grid::setPieceToPos(Piece* piece, const GridPos &pos) {
    _grid[pos.x][pos.y] = piece;
    _piecePositions[piece] = pos;
}

Grid::Grid(const std::list<Piece*> &pieces) : _pieces(pieces){
    memset(_grid, NULL, sizeof(GridDataType));
    /*
    bool useRandom = true;
    if(useRandom) {
        while (true) {
            GridPos pos;
            memset(_grid, NULL, sizeof(GridDataType));
            _piecePositions.clear();
            for (auto piece : _pieces) {
                do {
                    pos.x = rand() % GRID_X;
                    pos.y = rand() % GRID_Y;
                } while(pieceInPos(pos) != NULL);
                
                setPieceToPos(piece, pos);
            }
            if (IdCache::reserveId(calculateId())) {
                print();
                break;
            }
            else {
                Analytics::reportEvent("Grid Randomized");
            }
        }
        
    }
    else {
        // 4,1 0,0 0,4 1,3 3,2
        
        GridPos fixedPositions[5];
        fixedPositions[0].set(4,1);
        fixedPositions[1].set(0,4);
        fixedPositions[2].set(0,0);
        fixedPositions[3].set(1,3);
        fixedPositions[4].set(3,2);
        
        int i=0;
        for (auto piece : _pieces) {
            setPieceToPos(piece, fixedPositions[i++]);
        }
    }
     */
}

Grid::Grid(const Grid &copyFrom) : _pieces(copyFrom._pieces), _piecePositions(copyFrom._piecePositions), _moves(copyFrom._moves) {
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
                Analytics::reportEvent("Move explored");
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
    setPieceToPos(piece, newPos);
}

void Grid::print() const {
    GridPos pos;
    for (int y=GRID_Y-1; y >=0 ; y--) {
        pos.y = y;
        for (int x=0; x < GRID_X; x++) {
            pos.x = x;
            Piece *p = pieceInPos(pos);
            std::string code = "+";
            if (pos.x == 2 && pos.y == 2) {
                code = "x";
            }
            if (p != NULL) {
                //code = p->isSpecial() ? "S" : "O";
                code = std::to_string(p->getIdBase());
            }
            std::cout << code;
        }
        std::cout << std::endl;
    }
}

void Grid::printMoves() const {
    std::cout << buildMoveString() << std::endl;
}

bool Grid::isSolution() {
    return _grid[2][2] != NULL && _grid[2][2]->isSpecial();
}

int Grid::calculateId() {
    int id=0;
    for (auto piece : _pieces) {
        GridPos pos = positionOfPiece(piece);
        id += (pos.x*GRID_Y+pos.y)*pow(GRID_X*GRID_Y, piece->getIdBase());
    }
    return id;
}

Grid* Grid::createGridFromId(int potencialId, const std::list<Piece*> pieces) {
    Grid *grid = new Grid(pieces);
    
    int id = potencialId;
    for (auto piece : pieces) {
        int localId = id % (GRID_X*GRID_Y);
        GridPos localPos(localId / GRID_X, localId%GRID_Y);

        if (grid->pieceInPos(localPos) != NULL) {
            Analytics::reportEvent("grid index invalid");
            delete grid;
            return NULL;
        }
        grid->setPieceToPos(piece, localPos);
        id = id / (GRID_X*GRID_Y);
    }
    
    /*GridPos fixedPositions[6];
    fixedPositions[0].set(4,2);
    fixedPositions[1].set(0,4);
    fixedPositions[2].set(0,3);
    fixedPositions[3].set(0,2);
    fixedPositions[4].set(0,1);
    fixedPositions[5].set(0,0);
    
    int i=0;
    for (auto piece : pieces) {
        grid->setPieceToPos(piece, fixedPositions[i++]);
    }
    */
    return grid;
}

void Grid::addMove(Direction move, Piece *piece) {
    MoveElement el(piece->getIdBase(), move);
    _moves.push_back(el);
}

std::string Grid::buildMoveString() const {
    std::stringstream stream;
    for (auto move : _moves) {
        stream << std::to_string(move.first) << directionString(move.second) << " ";
    }
    return stream.str();
}
