
//    steffen benjamin
//    binary search benjamin

#include <stdio.h>
#include <stdlib.h>

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
void steffen_Que(passenger *pPassenger, passenger *pPassenger1, int passengers);

// Good
char GetSeatName(seatLetter letter);
void QueuePassengers(passenger passengers[3], int numPassengers, enum boardingProcedure procedure);
int passengerCompare(passenger* a, passenger* b);
void random_Que(passenger *passengers, passenger *sortedPassengers, int numPassengers);
void steffen_que(passenger *passengers, passenger *sorted_passengers, int numPassengers);
int binary_search(passenger *sorted_passengers, int seat, int row, int num_passengers);


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
void QueuePassengers(passenger passengers[3], int numPassengers, boardingProcedure procedure)
{
    passenger* passengersCopy = calloc(numPassengers, sizeof(passengers[0]));
    CopyArray(passengersCopy, passengers, numPassengers);
    qsort(passengersCopy, numPassengers, sizeof(passengers[0]), (compfn)passengerCompare);

    switch (procedure)
    {
        case Random:
            random_Que(passengers, passengersCopy, numPassengers);
            break;
        case SteffenModified:
            steffen_Que(passengers, passengersCopy, numPassengers);
            break;
    }
}

void CopyArray(passenger *to, passenger *from, int num)
{
    for (int i = 0; i < num; ++i)
    {
        to[i] = from[i];
    }
}

void random_Que(passenger *passengers, passenger *sortedPassengers, int numPassengers)
{
    int* takeSpots = calloc(numPassengers, sizeof(int));

    for (int i = 0; i < numPassengers; ++i)
    {
        int spot = getSpot(takeSpots, numPassengers);
        passengers[spot] = sortedPassengers[i];
        takeSpots[i] = 1;
    }
}

void steffen_Que(passenger *passengers, passenger *sorted_passengers, int numPassengers){
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
                if(ps_nr >= 0)
                    passengers[0] = sorted_passengers[ps_nr];

            }
            
        }
        
    }
    
}

int binary_search(passenger *sorted_passengers, int seat, int row, int num_passengers){
    int result = 0, i, middle_nr_rows = 33/2, middle_nr_seats = 189/2, middle_num_passengers = num_passengers/2;
    if (sorted_passengers[middle_num_passengers].seatPos.x > row)
        binary_search(sorted_passengers, seat, row, middle_nr_rows);

    else if (sorted_passengers[middle_num_passengers].seatPos.y < middle_nr_rows)
        binary_search(sorted_passengers, seat, row, middle_nr_rows);

    else if (sorted_passengers[middle_num_passengers].seatPos.y == middle_nr_rows){
                result = sorted_passengers[middle_num_passengers].seatPos.x;
    }
    else
        result = -1;
    
    return result;
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
    for (int i = 0; i < 3; ++i)
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

