// timer.cpp
#define SC_USE_SC_STRING_OLD
#include "timer.h"

void timer::runtimer() {
    while(true) {
        if (start) {
            cout << "Timer: timer start detected " << endl;
            count = 5;
            timeout = false;
            //start = false;
        } else {
            if (count > 0) {
                count--;
                timeout = false;
            } else {
                timeout = true;
            }
        }
        wait();
    }
}
