//
//  Analytics.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 09/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include "Analytics.h"
#include <iostream>

std::map<std::string, int> Analytics::_counters;

int Analytics::reportEvent(std::string eventName) {
    auto it = _counters.find(eventName);
    if (it != _counters.end()) {
        (it->second)++;
        return it->second;
    }
    else {
        _counters[eventName] = 1;
        return 1;
    }
}

void Analytics::dashboard() {
    std::cout << std::endl;
    std::cout << "Analytics" << std::endl;
    for (auto pair : _counters) {
        std::cout << pair.first + " " + std::to_string(pair.second) << std::endl;
    }
}