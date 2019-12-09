#include "..\Header.h"

#define LUGGAGE_STORE_TICKS 3

int test(passenger *passenger);

void stateLuggage(passenger *pArr, int i) {
    if(pArr[i].hasLuggage == STOWED_AWAY_LUGGAGE || pArr[i].hasLuggage == NO_LUGGAGE) {
        pArr[i].currState = Seating;
        return;
    }

    pArr[i].hasLuggage = STOWED_AWAY_LUGGAGE;
    pArr[i].ticksToWait = LUGGAGE_STORE_TICKS;
}
