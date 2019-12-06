#include "..\..\Header.h"

#define LUGGAGE_STORE_TICKS 3

void stateLuggage(passenger *pArr, int i) {
    if(pArr[i].hasLuggage == 2 || pArr[i].hasLuggage == 0) {
        pArr[i].currState = Seating;
        return;
    }

    pArr[i].hasLuggage = 2;
    pArr[i].ticksToWait = LUGGAGE_STORE_TICKS;
}