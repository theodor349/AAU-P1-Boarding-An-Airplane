#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define NO_LUGGAGE 0
#define HAS_LUGGAGE 1
#define STOWED_AWAY_LUGGAGE 2

typedef
struct point {
    int x, y;
} point;

typedef
struct boardingCalculation {
    int time;
    int procedure;
} boardingCalculation;

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
    int hasLuggage;
} passenger;

typedef
enum boardingProcedure {
    Raw = 0,
    Random,
    SteffenModified,
    BackToFront
} boardingProcedure;

typedef
enum seatLetter{
    Aisle = 0,
    C, B, A,
    D, E, F
} seatLetter;

typedef int (*compfn)(const void*, const void*);

// Simulation
float runSimulation(passenger *pArr, int pArrSize);
void convertSeatLetters(passenger *pArr, int pArrSize);
void updatePassenger(passenger *pArr, int pArrSize, int i);
void stateLookingForRow(passenger *pArr, int i);
void stateLuggage(passenger *pArr, int i);
void stateSeating(passenger *pArr, int pArrSize, int i);

//Looking For Row
int getPassengerAhead(passenger *pArr, int pIndex);

//Seating
int countPassengersInRow(passenger *pArr, int pArrSize, int pI);
int getClosestToAisle(passenger *pArr, int pArrSize, int pI);

// BoardingProcedure
char GetSeatName(seatLetter letter);
void QueuePassengers(passenger* passengers, int numPassengers, enum boardingProcedure procedure);
// Dummy
void generatePassengers(passenger passengers[3]);
void printPassenger(passenger passengers[3]);

//gather
int getPassengerAmount(FILE *passengerSource);
passenger* gather(FILE *passengerSource);
void readFile(passenger *passengerArray, FILE *passengerSource, int passengerAmount);


int timeCmp (boardingCalculation *a, boardingCalculation *b);
