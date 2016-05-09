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

class Analytics {
    static std::map<std::string, int> _counters;
public:
    static int reportEvent(std::string eventName);
    static void dashboard();
};

#endif /* defined(__LunarLockout__Analytics__) */
