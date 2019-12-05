#include "..\..\Header.h"

#define NO_PASSENGERS_AHEAD -1
#define STEP_DISTANCE 1

void stateLookingForRow(passenger *pArr, int i) {
    if(pArr[i].currPos.x == pArr[i].seatPos.x) {
        pArr[i].currState = pArr[i].hasLuggage ? Luggage : Seating;
        return;
    }

    int infront = getPassengerAhead(pArr, i);

    if(infront == NO_PASSENGERS_AHEAD) {
        pArr[i].currPos.x += STEP_DISTANCE;
    } else {
        // If the distance between two passengers is >= 2 Steps, the passenger behind can step forward
        if(pArr[infront].currPos.x - pArr[i].currPos.x >= STEP_DISTANCE * 2) {
            pArr[i].currPos.x += STEP_DISTANCE;
        }
    }
}


//Returns the index of the passenger ahead of the passenger with index pIndex.
//Returns -1 if no passenger is ahead.
int getPassengerAhead(passenger *pArr, int pIndex) {
    for(int i = pIndex - 1; i >= 0; --i) {
        if(pArr[i].currState != Idle)
            return i;
    }
    return NO_PASSENGERS_AHEAD;
}
