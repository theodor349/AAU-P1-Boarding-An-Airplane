
//    steffen benjamin
//    binary search benjamin

//
// Created by Theodor Risager on 29-11-2019.
// Copied by Benjamin Porsmose on 29-11-2019

#include <stdio.h>

typedef
struct point {
    float x, y;
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
enum seatletter{
    Aisle = 0,
    C, B, A,
    D, E, F
} seatletter;

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
char GetSeatName(seatletter letter);
void QueuePassengers(passenger passengers[3], int numPassengers, enum boardingProcedure procedure);
int passengerCompare(passenger* a, passenger* b);

void steffen_que(passenger *passengers, passenger *sorted_passengers, int numPassengers);
int binary_search(passenger *sorted_passengers, int seat, int row, int num_passengers);

int main(){
    passenger passengers[3];
    generatePassengers(passengers);
    printPassenger(passengers);

    QueuePassengers(passengers, 3, Random);

    printPassenger(passengers);

    return 0;
}
void QueuePassengers(passenger passengers[3], int numPassengers, boardingProcedure procedure)
{
    passenger* passengersCopy = calloc(numPassengers, sizeof(passengers[0]));
    int* takeSpots = calloc(numPassengers, sizeof(int));
    qsort(passengersCopy, numPassengers, sizeof(passengers[0]), (compfn)passengerCompare);

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


void steffen_que(passenger *passengers, passenger *sorted_passengers, int numPassengers){
    passenger* passengersCopy = calloc(numPassengers, sizeof(passengers[0]));
    int group = 0, row  = 0, seat = 0, check, place_in_que = 0, ps_nr = 0;

    for ( group = 0; group < 4; group++){
        for (row = (33 - (group/2)); row > 0 ; row-2){
            check = 0;
            for (seat = A ; seat > check; seat--){
                if (group % 2 != 0){
                    seat += 3;
                    check += 3;
                }
                ps_nr = binary_search(sorted_passengers, seat, row ,numPassengers);
                passengers[0] = sorted_passengers[ps_nr];
            }
            
        }
        
    }
    
}

int binary_search(passenger *sorted_passengers, int seat, int row, int num_passengers){
    int result = 0, i;
    sorted_passengers[i].seatPos.y;

    result = sorted_passengers;

    return result;
}



/*
 * Dummy stuff :D
 */

void printPassenger(passenger passengers[3])
{
    for (int i = 0; i < 3; ++i)
    {
        printf("%d row: %d, seat %c\n", i, (int) passengers[i].seatPos.x, GetSeatName((seatletter) passengers[i].seatPos.y));
    }
}

char GetSeatName(seatletter letter)
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
