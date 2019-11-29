#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

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

typedef
struct point {
    float x, y;
} point;

typedef
enum state { 
    LookingForRow = 0, 
    Luggage, 
    Seating, 
    Idle 
} state;

typedef
struct passenger {
    point currPos;
    point seatPos;
    state currState;
    int ticksToWait;
    bool hasLuggage;
} passenger;

float runSimulation(passenger *pArr, int n);
passenger updatePassenger(passenger p);
passenger stateLookingForRow(passenger p);
passenger stateLuggage(passenger p);
passenger stateSeating(passenger p);
int getPassengerAhead(passenger *pArr, int pIndex);
float getTimestep(void);
double gcd(double a, double b);

// This is here temporarily so we can compile the file and see if there are any errors
int main(void) {
    return 0;
}

float runSimulation(passenger *pArr, int n) {
    int tick = 0, seatedPassengers = 0;
    float timestep = getTimestep();

    //Keep ticking until all passengers are seated
    while(seatedPassengers < n) {

        for(int i = 0; i < n; ++i) {
            // If the passenger is idle do nothing
            if(pArr[i].currState == Idle) 
                continue;

            pArr[i] = updatePassenger(pArr[i]);
        }

        tick++;
    }

    return tick * timestep;
}

passenger updatePassenger(passenger p) {
    switch(p.currState) {
        case LookingForRow:
            stateLookingForRow(p);  break;
        case Luggage:
            stateLuggage(p);        break;
        case Seating:
            stateSeating(p);        break;
        default:
            printf("Something weird happened\n");
            break;
    }
    return p;
}

passenger stateLookingForRow(passenger p) {

    //DO SOMETHING WITH THE PASSENGER "P"

    return p;
}

passenger stateLuggage(passenger p) {

    //DO SOMETHING WITH THE PASSENGER "P"

    return p;
}

passenger stateSeating(passenger p) {

    //DO SOMETHING WITH THE PASSENGER "P"

    return p;
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