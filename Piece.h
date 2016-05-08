//
//  Piece.h
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#ifndef __LunarLockout__Piece__
#define __LunarLockout__Piece__

#include <stdio.h>
#include "Common.h"

class Grid;

class Piece {
    bool _isSpecial;
    
public:
    
    Piece(bool isSpecial);
    bool isSpecial() const;
    Grid* move(Direction dir, const Grid *inGrid);
};

#endif /* defined(__LunarLockout__Piece__) */
