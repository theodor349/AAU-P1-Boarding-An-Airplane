#include "..\..\Header.h"

#define LUGGAGE_STORE_TICKS 3

void stateLuggage(passenger *pArr, int i) {
	// If the passengers has stowed away their luggage go to next state
    if(pArr[i].hasLuggage == false) {
        pArr[i].currState = Seating;
        return;
    }

    // Set the passenger has luggage to stowed away
    pArr[i].hasLuggage = false;
    // Set time to wait
    pArr[i].ticksToWait = LUGGAGE_STORE_TICKS;
}