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
#include <algorithm>



std::map<std::string, int> Analytics::_counters;
std::map<std::string, std::clock_t*> Analytics::_runningTimers;
Analytics::AllTimersStorage Analytics::_allTimers;

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

void Analytics::insertTimerInstance(std::string timerName, double duration, Analytics::AllTimersStorage& storage) {
    auto it = storage.find(timerName);
    if (it == storage.end()) {
        storage[timerName] = std::vector<double>();
        it = storage.find(timerName);
    }
    
    it->second.push_back(duration);
}

void Analytics::startTimer(std::string timerName) {
    auto it = _runningTimers.find(timerName);
    if (it != _runningTimers.end()) {
        // timer already running. ignoring
        reportEvent("Timer starts ignored due to already running - " + timerName);
        return;
    }
    else {
        //std::clock_t *c = new std::clock_t(clock());
        _runningTimers[timerName] = new std::clock_t(clock());
    }
}

bool Analytics::endTimer(std::string timerName) {
    auto it = _runningTimers.find(timerName);
    if (it == _runningTimers.end()) {
        // timer not running. ignoring
        reportEvent("Timer ends ignored due to not running");
        return false;
    }
    else {
        double duration = (std::clock() - (*it->second)) / (double)CLOCKS_PER_SEC;
        
        insertTimerInstance(timerName, duration, _allTimers);
        _runningTimers.erase(it);
        
        return true;
    }
}

void Analytics::dashboard() {
    printCounters();
    printTimers();
    
}

void Analytics::printCounters() {
    std::cout << std::endl;
    std::cout << "Counters" << std::endl;
    for (auto pair : _counters) {
        std::cout << pair.first + " " + number_fmt(pair.second) << std::endl;
    }
}

void Analytics::printTimers() {
    std::cout << std::endl;
    std::cout << "Timers" << std::endl;
    for (auto pair:_allTimers) {
        double total = 0;
        double mn = 999999999;
        double mx = -mn;
        
        for (auto duration : pair.second) {
            total += duration;
            mn = std::min(duration, mn);
            mx = std::max(duration, mx);
        }
        std::cout << pair.first << " Total: " << total << " Avg: " << (total / (double)pair.second.size()) << " Count: " << number_fmt(pair.second.size()) << " min, max: " << mn << ", " << mx << std::endl;
    }
}