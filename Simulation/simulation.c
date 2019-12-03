#include "..\Header.h"

#define WALK_SPEED 1
#define LUGGAGE_STORE_TIME 1
#define CROSS_PASSENGER_TIME 0
#define SIT_TIME 0
#define PERSONAL_SPACE 1
#define DIST_TO_FIRST_ROW 1.91
#define ROW_WIDTH 0.8128
#define ROW_WIDTH_SPECIAL 1.0321    /* Row width for rows 1, 16 & 17 */
#define SEAT_WIDTH 1
#define MAX_ROWS 33
#define MAX_SEATS 189

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

    return tick * getTimestep();
}

void updatePassenger(passenger *pArr, int i) {
    switch(pArr[i].currState) {
        case LookingForRow:
            stateLookingForRow(pArr, i);  break;
        case Luggage:
            stateLuggage(pArr, i);        break;
        case Seating:
            stateSeating(pArr, i);        break;
        default:
            printf("Something weird happened\n");
            break;
    }
}

//Returns the index of the passenger ahead of the passenger with index pIndex.
//Returns -1 if no passenger is ahead.
int getPassengerAhead(passenger *pArr, int pIndex) {
    for(int i = pIndex - 1; i >= 0; --i) {
        if(pArr[i].currState != Idle)
            return i;
    }
    return -1;
}

float getTimestep(void) {
    float t = gcd(WALK_SPEED, LUGGAGE_STORE_TIME);
    t = gcd(t, CROSS_PASSENGER_TIME);
    t = gcd(t, SIT_TIME);
    return t;
}

/* Found on Stack Exchange. */
double gcd(double a, double b) {
    if (a < b) return gcd(b, a);
    if (fabs(b) < 0.001) return a;
    else return (gcd(b, a - floor(a / b) * b));
}
