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
void updatePassenger(passenger *pArr, int i);
void stateLookingForRow(passenger *pArr, int i);
void stateLuggage(passenger *pArr, int i);
void stateSeating(passenger *pArr, int i);
int getPassengerAhead(passenger *pArr, int pIndex);
float getTimestep(void);
double gcd(double a, double b);
