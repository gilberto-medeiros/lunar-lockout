//
//  Analytics.cpp
//  LunarLockout
//
//  Created by Gilberto Medeiros on 09/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#include "Analytics.h"
#include <iostream>
#include <sstream>

std::map<std::string, int> Analytics::_counters;

//http://stackoverflow.com/questions/7257956/how-to-insert-spaces-in-a-big-number-to-make-it-more-readable
std::string number_fmt(unsigned long long n, char sep = ',') {
    std::stringstream fmt;
    fmt << n;
    std::string s = fmt.str();
    s.reserve(s.length() + s.length() / 3);
    
    // loop until the end of the string and use j to keep track of every
    // third loop starting taking into account the leading x digits (this probably
    // can be rewritten in terms of just i, but it seems more clear when you use
    // a seperate variable)
    for (int i = 0, j = 3 - s.length() % 3; i < s.length(); ++i, ++j)
        if (i != 0 && j % 3 == 0)
            s.insert(i++, 1, sep);
    
    return s;
}

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
        std::cout << pair.first + " " + number_fmt(pair.second) << std::endl;
    }
}