//
// Created by Theodor Risager on 29-11-2019.
//

#include <stdio.h>

typedef
struct point {
    float x, y;
} point;

typedef
enum boardingProcedure{
    Random,
    SteffenModified
};

typedef
enum state {
    LookingForRow = 0,
    Luggage,
    Seating,
    Idle
} state;

typedef
enum rowLetter{
    Aisle = 0,
    C, B, A,
    D, E, F
} rowLetter;

typedef
struct passenger {
    point currPos;
    point seatPos;
    state currState;
    int ticksToWait;
    int hasLuggage;
} passenger;

void generatePassengers(passenger passengers[3]);

void printPassenger(passenger passengers[3]);

char GetSeatName(rowLetter letter);

void QueuePassengers(passenger passengers[3], int numPassengers, enum boardingProcedure procedure);

int main()
{
    passenger passengers[3];
    generatePassengers(passengers);
    printPassenger(passengers);

    QueuePassengers(passengers, 3, Random);

    return 0;
}

void QueuePassengers(passenger passengers[3], int numPassengers, enum boardingProcedure procedure)
{
    
}


/*
 * Dummy stuff :D
 */

void printPassenger(passenger passengers[3])
{
    for (int i = 0; i < 3; ++i)
    {
        printf("%d row: %d, seat %c\n", i, (int) passengers[i].seatPos.x, GetSeatName((rowLetter) passengers[i].seatPos.y));
    }
}

char GetSeatName(rowLetter letter)
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
