#include <stdio.h>
#include <stdlib.h>
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

typedef
enum boardingProcedure{
    Random,
    SteffenModified
}boardingProcedure;

typedef
enum seatLetter{
    Aisle = 0,
    C, B, A,
    D, E, F
} seatLetter;

typedef int (*compfn)(const void*, const void*);

// Simulation
float runSimulation(passenger *pArr, int n);
void updatePassenger(passenger *pArr, int i);
void stateLookingForRow(passenger *pArr, int i);
void stateLuggage(passenger *pArr, int i);
void stateSeating(passenger *pArr, int i);
int getPassengerAhead(passenger *pArr, int pIndex);
float getTimestep(void);
double gcd(double a, double b);

// BoardingProcedure
char GetSeatName(seatLetter letter);
void QueuePassengers(passenger* passengers, int numPassengers, enum boardingProcedure procedure);
int passengerCompare(passenger* a, passenger* b);
void random_Que(passenger *passengers, passenger *sortedPassengers, int numPassengers);
int binary_search(passenger *sorted_passengers, int seat, int row, int num_passengers);
void steffen_que(passenger *passengers, passenger *sorted_passengers, int numPassengers);
int getRandomSpot(int *takenSpots, int numPassengers);
void CopyArray(passenger *to, passenger *from, int num);
// Dummy
void generatePassengers(passenger passengers[3]);
void printPassenger(passenger passengers[3]);