#include "..\..\Header.h"

#define LUGGAGE_STORE_TICKS 3

void stateLuggage(passenger *pArr, int i) {
    pArr[i].hasLuggage = 0;
    pArr[i].ticksToWait = LUGGAGE_STORE_TICKS;
    pArr[i].currState = Seating;
}
