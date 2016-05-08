//
//  GridPos.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include "GridPos.h"

GridPos::GridPos() : x(0), y(0) {

}

GridPos::GridPos(const GridPos &copyFrom) : x(copyFrom.x), y(copyFrom.y) {
    
}

GridPos::GridPos(int ix, int iy) : x(ix), y(iy) {
    
};

GridPos GridPos::operator+(const GridPos &other) const{
    return GridPos(x+other.x, y+other.y);

}

void GridPos::operator+=(const GridPos &other) {
    x += other.x;
    y += other.y;
}

bool GridPos::operator==(const GridPos &other) const {
    return x == other.x && y == other.y;
}

void GridPos::set(int ix, int iy) {
    x = ix;
    y = iy;
}

GridPos& directionToVec(Direction dir) {
    static GridPos up(0, 1);
    static GridPos down(0, -1);
    static GridPos left(-1, 0);
    static GridPos right(1, 0);
    
    switch (dir) {
        case UP:
            return up;
        case DOWN:
            return down;
        case LEFT:
            return left;
        case RIGHT:
            return right;
        default:
            // very strange error
            return up;
    }
}
