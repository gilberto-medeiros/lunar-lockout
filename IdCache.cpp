//
//  IdCache.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 09/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include "IdCache.h"

std::set<int> IdCache::_ids;

bool IdCache::reserveId(int id) {
    auto it = _ids.find(id);
    if (it != _ids.end()) {
        return false;
    }else {
        _ids.insert(id);
        return true;
    }
}

void IdCache::clear() {
    _ids.clear();
}