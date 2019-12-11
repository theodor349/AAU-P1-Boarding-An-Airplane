#include "..\Header.h"

#define WALK_SPEED 1
#define LUGGAGE_STORE_TIME 1
#define CROSS_PASSENGER_TIME 0
#define SIT_TIME 0
#define MAX_ROWS 33
#define MAX_SEATS 189
#define TIMESTEP_IN_SECONDS 0.45

void resetPassengers(passenger *passengers, int numPassengers);

float runSimulation(passenger *pArr, int pArrSize) {
    int tick = 0, seatedPassengers = 0;

    // Make sure all passenger data is as expected
    resetPassengers(pArr, pArrSize);

    // Keep ticking until all passengers are seated
    while(seatedPassengers < pArrSize) {

        for(int i = 0; i < pArrSize; ++i) {
            // If the passenger is idle do nothing
            if(pArr[i].currState == Idle)
                continue;

            // Decrement ticks to wait or update the passenger
            if(pArr[i].ticksToWait > 0)
                pArr[i].ticksToWait--;
            else
                updatePassenger(pArr, pArrSize, i);

            // If the passenger has entered the Idle state increment seated passengers by 1
            if(pArr[i].currState == Idle)
                seatedPassengers++;
        }

        tick++;
    }

    return tick * TIMESTEP_IN_SECONDS;
}

void resetPassengers(passenger *passengers, int numPassengers) {
    convertSeatLetters(passengers, numPassengers);
    for (int i = 0; i < numPassengers; ++i) {
        passengers[i].currPos.x = -1 - i;
        passengers[i].currPos.y = 0;
        passengers[i].currState = LookingForRow;
        passengers[i].ticksToWait = 0;
        if(passengers[i].hasLuggage == STOWED_AWAY_LUGGAGE)
            passengers[i].hasLuggage = HAS_LUGGAGE;
    }
}

void convertSeatLetters(passenger *pArr, int pArrSize) {
    for(int i = 0; i < pArrSize; i++) {
        switch(pArr[i].seatPos.y) {
            case D:
                pArr[i].seatPos.y = -1;
                break;
            case E:
                pArr[i].seatPos.y = -2;
                break;
            case F:
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