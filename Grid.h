//
//  Grid.h
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#ifndef __LunarLockout__Grid__
#define __LunarLockout__Grid__

#include <stdio.h>
#include <list>
#include <map>
#include "Common.h"
#include "Piece.h"
#include "GridPos.h"

class Piece;

typedef Piece *GridDataType[GRID_X][GRID_Y];
typedef std::map<Piece*, GridPos> PieceToPositionMap;
typedef std::pair<int,Direction> MoveElement;
typedef std::list<MoveElement> MoveList;

class Grid {
    GridDataType _grid;
    std::list<Piece*> _pieces;
    PieceToPositionMap _piecePositions;
    MoveList _moves;
    
    void setPieceToPos(Piece* piece, const GridPos &pos);
    
public:
    Grid(const std::list<Piece*> &pieces);
    Grid(const Grid &copyFrom);
    //~Grid();
    
    const std::list<Piece*> getPieces() const;
    std::list<Grid*> computeAllMoves() const;
    
    GridPos positionOfPiece(Piece* piece) const;
    Piece* pieceInPos(GridPos &pos) const;
    
    void swapPieceToPos(Piece* piece, const GridPos &newPos);
    
    void print() const;
    void printMoves() const;
    bool isSolution();
    
    int calculateId();
    static Grid* createGridFromId(int potencialId, const std::list<Piece*> pieces);
    
    void addMove(Direction move, Piece *piece);
    std::string buildMoveString() const;
};


#endif /* defined(__LunarLockout__Grid__) */
