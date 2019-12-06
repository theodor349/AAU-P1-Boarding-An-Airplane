#include "..\Header.h"

#define WALK_SPEED 1
#define LUGGAGE_STORE_TIME 1
#define CROSS_PASSENGER_TIME 0
#define SIT_TIME 0
#define MAX_ROWS 33
#define MAX_SEATS 189
#define TIMESTEP_IN_SECONDS 1

float runSimulation(passenger *pArr, int pArrSize) {
    int tick = 0, seatedPassengers = 0;

    convertSeatLetters(pArr, pArrSize);

    //Keep ticking until all passengers are seated
    while(seatedPassengers < pArrSize) {

        for(int i = 0; i < pArrSize; ++i) {
            // If the passenger is idle do nothing
            if(pArr[i].currState == Idle)
                continue;

            if(pArr[i].ticksToWait > 0)
                pArr[i].ticksToWait--;
            else
                updatePassenger(pArr, pArrSize, i);

            if(pArr[i].currState == Idle)
                seatedPassengers++;

            /*
            printf("i: %d, pos(%2d,%2d), seatPos(%2d,%2d), state: %d, wait: %d, luggage: %d\n", i,
            pArr[i].currPos.x, pArr[i].currPos.y, 
            pArr[i].seatPos.x, pArr[i].seatPos.y,
            (int)pArr[i].currState, pArr[i].ticksToWait, pArr[i].hasLuggage);
            */            
        }

        tick++;
    }

    return tick * TIMESTEP_IN_SECONDS;
}

void convertSeatLetters(passenger *pArr, int pArrSize) {
    for(int i = 0; i < pArrSize; i++) {
        switch(pArr[i].seatPos.y) {
            case 4:
               pArr[i].seatPos.y = -1;
               break;
            case 5:
                pArr[i].seatPos.y = -2;
                break;
            case 6:
                pArr[i].seatPos.y = -3;
                break;
        }
    }
}

void updatePassenger(passenger *pArr, int pArrSize, int i) {
    switch(pArr[i].currState) {
        case LookingForRow:
            stateLookingForRow(pArr, i);
            break;
        case Luggage:
            stateLuggage(pArr, i);
            break;
        case Seating:
            stateSeating(pArr, pArrSize, i);
            break;
        default:
            printf("Error on passenger state assignment\n");
            break;
    }
}