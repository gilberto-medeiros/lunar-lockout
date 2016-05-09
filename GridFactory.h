//
//  GridFactory.h
//  LunarLockout
//
//  Created by Gilberto Medeiros on 09/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#ifndef __LunarLockout__GridFactory__
#define __LunarLockout__GridFactory__

#include <stdio.h>
#include <list>

class Grid;
class Piece;

class GridFactory {
private:
    std::list<int> _freeIds;
    int _nextFreeId;
    int _totalGrids;
    
    static GridFactory *_instance;
public:
    static void initialiseWithNumberOfPieces(int numberOfPieces);
    static Grid *createGrid(const std::list<Piece*> pieces);
};

#endif /* defined(__LunarLockout__GridFactory__) */
