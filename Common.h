//
//  Common.h
//  LunarLockout
//
//  Created by Gilberto Medeiros on 06/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#ifndef LunarLockout_Common_h
#define LunarLockout_Common_h

#include "Analytics.h"

#define GRID_X 5
#define GRID_Y 5

enum  Direction {
    UP =0,
    DOWN =1,
    LEFT =2,
    RIGHT =3,
    COUNT =4
};

inline std::string directionString(Direction dir) {
    switch (dir) {
        case UP:
            return "U";
        case DOWN:
            return "D";
        case LEFT:
            return "L";
        case RIGHT:
            return "R";
        case COUNT:
            return "COUNT";
    }
}




#endif
