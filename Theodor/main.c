#include <stdio.h>
#include <stdlib.h>
#define ROWS 33

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
void steffenQue(passenger *passengers, passenger *sorted_passengers, int numPassengers);

// Good
char GetSeatName(seatLetter letter);
void QueuePassengers(passenger passengers[3], int numPassengers, enum boardingProcedure procedure);
int passengerCompare(passenger* a, passenger* b);
void randomQue(passenger *passengers, passenger *sortedPassengers, int numPassengers);
void steffenQue(passenger *passengers, passenger *sorted_passengers, int numPassengers);
int binarySearch(passenger *sortedPassengers, seatLetter seat, int row, int numPassengers);


int getSpot(int *takenSpots, int numPassengers);

void CopyArray(passenger *to, passenger *from, int num);

int main()
{
    passenger passengers[3];
    generatePassengers(passengers);
    printPassenger(passengers);

    QueuePassengers(passengers, 3, SteffenModified);

    printf("\n");
    printPassenger(passengers);
    return 0;
}

// CALLED FROM MAIN FUNCTION
void QueuePassengers(passenger passengers[3], int numPassengers, boardingProcedure procedure){
    int i;
    passenger* passengersCopy = calloc(numPassengers, sizeof(passengers[0]));
    CopyArray(passengersCopy, passengers, numPassengers);
    qsort(passengersCopy, numPassengers, sizeof(passengers[0]), (compfn)passengerCompare);

    switch (procedure)
    {
        case Random:
            randomQue(passengers, passengersCopy, numPassengers);
            break;
        case SteffenModified:
            steffenQue(passengers, passengersCopy, numPassengers);
            break;
    }
}

void CopyArray(passenger *to, passenger *from, int num){
    int i;
    for ( i = 0; i < num; ++i)
    {
        to[i] = from[i];
    }
}

void randomQue(passenger *passengers, passenger *sortedPassengers, int numPassengers)
{
    int* takeSpots = calloc(numPassengers, sizeof(int)), i;

    for (i = 0; i < numPassengers; ++i)
    {
        int spot = getSpot(takeSpots, numPassengers);
        passengers[spot] = sortedPassengers[i];
        takeSpots[i] = 1;
    }
}

void steffenQue(passenger *passengers, passenger *sorted_passengers, int numPassengers){
    int group, row, seat, check, placeInQue = 0, p;

    // For all groups (Even A-C, UnEven A-C, Even F-D, UnEven F-D)
    for (group = 0; group < 4; group++){
        // For every second Row
        for (row = (ROWS - (group/2)); row > 0 ; row -= 2){
            check = 0;
            // Start a the window
            seat = A;
            // If F-C increase by 3
            if (group % 2 != 0){
                seat += 3;
                check += 3;
            }
            // For each seat from A-C or F-D
            for (seat; seat > check; seat--){
                p = binarySearch(sorted_passengers, seat, row, numPassengers);
                // If a passenger with this Row and Seat is found
                if(p != -1){
                    passengers[placeInQue] = sorted_passengers[p];
                    placeInQue++;
                }
            }
        }
    }
}

int binarySearch(passenger *sortedPassengers, seatLetter seat, int row, int numPassengers){
    int left = 0, right = numPassengers, middle;
    while (left < right){
        // Get middle
        middle = (left + right) * 0.5;
        passenger p = sortedPassengers[middle];

        // If passenger row is less than Row
        if (p.seatPos.x < row)
            right = middle;
        // If passenger row is correct
        else if (p.seatPos.x == row)
        {
            // If passenger seat is less than seat
            if (p.seatPos.y < seat)
                left = middle + 1;
            // If the right seat and row have been found
            else if (p.seatPos.y == seat)
                return middle;
            else
                right = middle;
        }
        else
            left = middle + 1;
    }
    // Return -1 if nothing was found
    return -1;
}

int getSpot(int *takenSpots, int numPassengers)
{
    int index = rand() % numPassengers;
    while (takenSpots[index])
    {
        index++;
        index %= numPassengers;
    }

    return index;
}

int passengerCompare(passenger* a, passenger* b)
{
    int r = a->seatPos.x - b->seatPos.y;
    if(r != 0)
        return r;

    int ay = a->seatPos.y < 4 ? a->seatPos.y + 6 : a->seatPos.y;
    int by = b->seatPos.y < 4 ? b->seatPos.y + 6 : b->seatPos.y;

    return  ay -by;
}

/*
 * Dummy stuff :D
 */


void printPassenger(passenger passengers[3])
{
    int i;
    for ( i = 0; i < 3; ++i)
    {
        printf("%d row: %d, seat %c\n", i, (int) passengers[i].seatPos.x, GetSeatName((seatLetter) passengers[i].seatPos.y));
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

