#include "..\Header.h"

#define WALK_SPEED 1
#define LUGGAGE_STORE_TIME 1
#define CROSS_PASSENGER_TIME 0
#define SIT_TIME 0
#define MAX_ROWS 33
#define MAX_SEATS 189
#define TIMESTEP_IN_SECONDS 1

float runSimulation(passenger *pArr, int n) {
    int tick = 0, seatedPassengers = 0;

    //Keep ticking until all passengers are seated
    while(seatedPassengers < n) {

        for(int i = 0; i < n; ++i) {
            // If the passenger is idle do nothing
            if(pArr[i].currState == Idle)
                continue;

            if(pArr[i].ticksToWait > 0)
                pArr[i].ticksToWait--;
            else
                updatePassenger(pArr, i);
        }

        tick++;
    }

    return tick * TIMESTEP_IN_SECONDS;
}

void updatePassenger(passenger *pArr, int i) {
    switch(pArr[i].currState) {
        case LookingForRow:
            stateLookingForRow(pArr, i);
            break;
        case Luggage:
            stateLuggage(pArr, i);
            break;
        case Seating:
            stateSeating(pArr, i);
            break;
        default:
            printf("Error on passenger state assignment\n");
            break;
    }
}
