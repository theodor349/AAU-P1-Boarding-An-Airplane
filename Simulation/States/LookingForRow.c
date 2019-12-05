#include "..\..\Header.h"

#define STEP_DISTANCE 1

void stateLookingForRow(passenger *pArr, int i) {
    if(pArr[i].currPos.x == pArr[i].seatPos.x) {
        pArr[i].currState = pArr[i].hasLuggage ? Luggage : Seating;
        return;
    }    

    int infront = getPassengerAhead(pArr, i);

    if(infront == -1) {
        pArr[i].currPos.x += STEP_DISTANCE;
    } else {
        // If the distance between two passengers is >= 2 Steps, the passenger behind can step forward
        if(pArr[infront].currPos.x - pArr[i].currPos.x >= STEP_DISTANCE * 2) {
            pArr[i].currPos.x += STEP_DISTANCE;
        }
    }
}