//
// Created by Theodor Risager on 29-11-2019.
//

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

int main()
{
    passenger passengers[3];
    generatePassengers(passengers);
    printPassenger(passengers);

    printf("\n Random\n");
    QueuePassengers(passengers, 3, Random);
    printPassenger(passengers);

    printf("\n Steffen\n");
    QueuePassengers(passengers, 3, SteffenModified);
    printPassenger(passengers);

    return 0;
}

// CALLED FROM MAIN FUNCTION
void QueuePassengers(passenger* passengers, int numPassengers, boardingProcedure procedure)
{
    passenger* passengersCopy = calloc(numPassengers, sizeof(passengers[0]));
    // Copy all passengers to a new array
    CopyArray(passengersCopy, passengers, numPassengers);
    // Sort the new array
    qsort(passengersCopy, numPassengers, sizeof(passengers[0]), (compfn)passengerCompare);

    // Call the correct procedure
    switch (procedure)
    {
        case Random:
            random_Que(passengers, passengersCopy, numPassengers);
            break;
        case SteffenModified:
            steffen_que(passengers, passengersCopy, numPassengers);
            break;
    }
}

// Copies an array over to a new array
void CopyArray(passenger *to, passenger *from, int num)
{
    for (int i = 0; i < num; ++i)
    {
        to[i] = from[i];
    }
}

// Shuffles the passengers randomly
void random_Que(passenger *passengers, passenger *sortedPassengers, int numPassengers)
{
    int* takeSpots = calloc(numPassengers, sizeof(int));

    // For each passenger
    for (int i = 0; i < numPassengers; ++i)
    {
        // Get a random seat
        int spot = getRandomSpot(takeSpots, numPassengers);
        // Assign the passenger
        passengers[spot] = sortedPassengers[i];
        // Increment taken spots
        takeSpots[i] = 1;
    }
}

void steffen_que(passenger *passengers, passenger *sorted_passengers, int numPassengers){
}

int binary_search(passenger *sorted_passengers, int seat, int row, int num_passengers){
    return 1;
}

// returns a random index which is not taken
int getRandomSpot(int *takenSpots, int numPassengers)
{
    int index = rand() % numPassengers;
    // Increment by 1 while spot is not taken
    while (takenSpots[index])
    {
        index++;
        index %= numPassengers;
    }

    return index;
}

// Compares two passengers
int passengerCompare(passenger* a, passenger* b)
{
    // Row
    int r = a->seatPos.x - b->seatPos.y;
    if(r != 0)
        return r;

    // Place in row A (A B C, F E D)
    int ay = a->seatPos.y < 4 ? a->seatPos.y + 6 : a->seatPos.y;
    int by = b->seatPos.y < 4 ? b->seatPos.y + 6 : b->seatPos.y;
    return  ay - by;
}

/*
 * Dummy stuff :D
 */

void printPassenger(passenger passengers[3])
{
    for (int i = 0; i < 3; ++i)
    {
        printf("%d row: %d, seat %c\n", i, passengers[i].seatPos.x, GetSeatName((seatLetter) passengers[i].seatPos.y));
    }
}

char GetSeatName(seatLetter letter)
{
    switch (letter)
    {
        case Aisle:
            return 'N';
        case C:
            return 'C';
        case B:
            return 'B';
        case A:
            return 'A';
        case D:
            return 'D';
        case E:
            return 'E';
        case F:
            return 'F';
    }
}

void generatePassengers(passenger passengers[3])
{
    passenger temp;
    point p;

    p.x = 1;
    p.y = F;
    temp.seatPos = p;
    passengers[0] = temp;

    p.x = 3;
    p.y = A;
    temp.seatPos = p;
    passengers[1] = temp;

    p.x = 3;
    p.y = F;
    temp.seatPos = p;
    passengers[2] = temp;
}
