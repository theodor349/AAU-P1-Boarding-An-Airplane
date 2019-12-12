#include "..\..\Header.h"

//The luggage store time is 25 ticks, but because of loop arithmetic it set to 24
#define LUGGAGE_STORE_TICKS 24

void stateLuggage(passenger *pArr, int i) {
	// If the passengers has no luggage or has stowed it away
    if(pArr[i].hasLuggage == STOWED_AWAY_LUGGAGE || pArr[i].hasLuggage == NO_LUGGAGE) {
        pArr[i].currState = Seating;
        return;
    }

    // Set the passenger has luggage to stowed away
    pArr[i].hasLuggage = STOWED_AWAY_LUGGAGE;
    // Set time to wait
    pArr[i].ticksToWait = LUGGAGE_STORE_TICKS;
}
