#include "..\..\Header.h"

#define PERSONAL_SPACE 1

void stateLookingForRow(passenger *pArr, int i) {

    float moveRate = 1; // fix moveRate, might be wrong. Was undefined

    if(pArr[i].currPos.x == pArr[i].seatPos.x) {
        pArr[i].currState = pArr[i].hasLuggage ? Luggage : Seating;
        return;
    }

    // fix moveRate, might be wrong. Was tickrate
    float newX = pArr[i].currPos.x + moveRate;
    if(newX > pArr[i].seatPos.x)
        newX = pArr[i].seatPos.x;

    int infront = getPassengerAhead(pArr, i);
    if(infront == -1) {
        pArr[i].currPos.x = newX;
    } else {
        if(pArr[infront].currPos.x - newX >= PERSONAL_SPACE) {
            pArr[i].currPos.x = newX;
        }
    }
}
