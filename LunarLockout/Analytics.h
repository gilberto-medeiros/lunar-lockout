//
//  Analytics.h
//  LunarLockout
//
//  Created by Gilberto Medeiros on 09/05/16.
//  Copyright (c) 2016 Gilberto Medeiros. All rights reserved.
//

#ifndef __LunarLockout__Analytics__
#define __LunarLockout__Analytics__

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <cstdio>
#include <ctime>
/*
namespace std {
    class clock_t;
}*/

class Analytics {
    static std::map<std::string, int> _counters;
    static std::map<std::string, std::clock_t*> _runningTimers;
    
    typedef std::map<std::string, std::vector<double>> AllTimersStorage;
    static AllTimersStorage _allTimers;
    
    static void insertTimerInstance(std::string timerName, double duration, AllTimersStorage& storage);
    
public:
    static int reportEvent(std::string eventName);
    
    static void startTimer(std::string timerName);
    static bool endTimer(std::string timerName);
    
    static void dashboard();
    static void printCounters();
    static void printTimers();
};

#endif /* defined(__LunarLockout__Analytics__) */
