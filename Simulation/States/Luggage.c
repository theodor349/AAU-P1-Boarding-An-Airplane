#include "..\..\Header.h"

#define LUGGAGE_STORE_TICKS 3

void stateLuggage(passenger *pArr, int i) {
	// If the passengers has no luggage or has stowed it away
    if(pArr[i].hasLuggage == 0 || pArr[i].hasLuggage == 2) {
        pArr[i].currState = Seating;
        return;
    }

    // Set the passenger has luggage to stowed away
    pArr[i].hasLuggage = 2;
    // Set time to wait
    pArr[i].ticksToWait = LUGGAGE_STORE_TICKS;
}