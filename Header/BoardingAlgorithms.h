#include <stdio.h>
#include <stdlib.h>

typedef
struct point {
    int x, y;
} point;

typedef
enum boardingProcedure{
    Random,
    SteffenModified
}boardingProcedure;

typedef
enum state {
    LookingForRow = 0,
    Luggage,
    Seating,
    Idle
} state;

typedef
enum seatLetter{
    Aisle = 0,
    C, B, A,
    D, E, F
} seatLetter;

typedef
struct passenger {
    point currPos;
    point seatPos;
    state currState;
    int ticksToWait;
    int hasLuggage;
} passenger;

typedef int (*compfn)(const void*, const void*);

// Dummy
void generatePassengers(passenger passengers[3]);
void printPassenger(passenger passengers[3]);

// Good
char GetSeatName(seatLetter letter);
void QueuePassengers(passenger* passengers, int numPassengers, enum boardingProcedure procedure);
int passengerCompare(passenger* a, passenger* b);
void random_Que(passenger *passengers, passenger *sortedPassengers, int numPassengers);
int binary_search(passenger *sorted_passengers, int seat, int row, int num_passengers);
void steffen_que(passenger *passengers, passenger *sorted_passengers, int numPassengers);
int getRandomSpot(int *takenSpots, int numPassengers);
void CopyArray(passenger *to, passenger *from, int num);
