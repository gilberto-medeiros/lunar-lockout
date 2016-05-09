//
//  IdCache.h
//  LunarLockout
//
//  Created by Gilberto Medeiros on 09/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#ifndef __LunarLockout__IdCache__
#define __LunarLockout__IdCache__

#include <stdio.h>

#include <set>

class IdCache {
private:
    static std::set<int> _ids;
public:
    static bool reserveId(int id);
};

#endif /* defined(__LunarLockout__IdCache__) */
