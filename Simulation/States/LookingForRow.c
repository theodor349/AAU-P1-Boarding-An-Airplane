#include "..\..\Header.h"

#define NO_PASSENGERS_AHEAD -1
#define STEP_DISTANCE 1

void stateLookingForRow(passenger *pArr, int i) {
    // Is the passenger is at the correct row?
    if(pArr[i].currPos.x == (pArr[i].seatPos.x * 2) - 1) {
        // Move on to next state
        pArr[i].currState = pArr[i].hasLuggage ? Luggage : Seating;
        return;
    }

    // Get index of the passenger in front (-1 if none)
    int infront = getPassengerAhead(pArr, i);

    // Is there a passenger infront?
    if(infront == NO_PASSENGERS_AHEAD) {
        // Move forward
        pArr[i].currPos.x += STEP_DISTANCE;
    } else {
        // Is the distance between two passengers is >= 2 Steps
        if(pArr[infront].currPos.x - pArr[i].currPos.x >= STEP_DISTANCE * 2) {
            // Move forward
            pArr[i].currPos.x += STEP_DISTANCE;
        }
    }
}


// Returns the index of the passenger ahead of the passenger with index pIndex.
// Returns -1 if no passenger is ahead.
int getPassengerAhead(passenger *pArr, int pIndex) {
    // For each passenger infront 
    for(int i = pIndex - 1; i >= 0; --i) {
        // Is passenger Idle/Seated?
        if(pArr[i].currState != Idle)
            return i;
    }
    return NO_PASSENGERS_AHEAD;
}
