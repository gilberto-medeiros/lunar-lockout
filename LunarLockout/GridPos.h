//
//  GridPos.h
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#ifndef __LunarLockout__GridPos__
#define __LunarLockout__GridPos__

#include <stdio.h>
#include "Common.h"

struct GridPos {
    int x;
    int y;

    GridPos();
    GridPos(const GridPos &copyFrom);
    GridPos(int ix, int iy);
    GridPos operator+(const GridPos &other) const;
    void operator+=(const GridPos &other);
    bool operator==(const GridPos &other) const;
    
    void set(int ix, int iy);
};

GridPos& directionToVec(Direction dir);

#endif /* defined(__LunarLockout__GridPos__) */
