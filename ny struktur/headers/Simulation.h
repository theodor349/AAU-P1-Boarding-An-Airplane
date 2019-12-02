#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

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