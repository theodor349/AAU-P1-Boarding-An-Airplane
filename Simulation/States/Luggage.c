#include "..\..\Header.h"

#define LUGGAGE_STORE_TIME 1

void stateLuggage(passenger *pArr, int i) {
    pArr[i].hasLuggage = false;
    pArr[i].ticksToWait = LUGGAGE_STORE_TIME / getTimestep();
    pArr[i].currState = Seating;
}
