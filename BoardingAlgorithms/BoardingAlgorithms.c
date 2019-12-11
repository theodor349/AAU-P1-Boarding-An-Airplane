#include "..\Header.h"
#define ROWS 33

void testFunction();
void randomQue(passenger *passengers, int numPassengers);
void backToFrontQue(passenger *passengers, passenger *sorted_passengers, int numPassengers);
void steffenQue(passenger *passengers, passenger *sorted_passengers, int numPassengers);
int binarySearch(passenger *sortedPassengers, seatLetter seat, int row, int numPassengers);
int passengerCompare(passenger* a, passenger* b);
int getRandomSpot(int *takenSpots, int numPassengers);
void CopyArray(passenger *to, passenger *from, int num);
void convertSeatLettersBack(passenger *passengers, int numPassengers);
void knuthShuffle(passenger *passengers, int start, int end);
int randIndex(int i, int end);
void swap(passenger *passengers, int iA, int iB);

void testFunction()
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
}

// CALLED FROM MAIN FUNCTION
void QueuePassengers(passenger* passengers, int numPassengers, boardingProcedure procedure)
{
    srand(time(NULL)); 

    // Convert seatletters from simulation to boarding stadard
    convertSeatLettersBack(passengers, numPassengers);

    passenger* passengersCopy = calloc(numPassengers, sizeof(passengers[0]));
    // Copy all passengers to a new array
    CopyArray(passengersCopy, passengers, numPassengers);
    // Sort the new array
    qsort(passengersCopy, numPassengers, sizeof(passengers[0]), (compfn)passengerCompare);

    // Call the correct procedure
    switch (procedure)
    {
        case Random:
            randomQue(passengers, numPassengers);
            break;
        case SteffenModified:
            steffenQue(passengers, passengersCopy, numPassengers);
            break;
        case BackToFront:
            backToFrontQue(passengers, passengersCopy, numPassengers);
            break;
    }

    free(passengersCopy);
}

void convertSeatLettersBack(passenger *passengers, int numPassengers)
{
    for (int i = 0; i < numPassengers; ++i)
    {
        switch(passengers[i].seatPos.y) {
            case -1:
                passengers[i].seatPos.y = D;
                break;
            case -2:
                passengers[i].seatPos.y = E;
                break;
            case -3:
                passengers[i].seatPos.y = F;
                break;
        }
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
void randomQue(passenger *passengers, int numPassengers) {
    knuthShuffle(passengers, 0, numPassengers);
}

void backToFrontQue(passenger *passengers, passenger *sorted_passengers, int numPassengers) {
    int mid = numPassengers / 2;
    knuthShuffle(sorted_passengers, 0, mid);
    knuthShuffle(sorted_passengers, mid, numPassengers);
    CopyArray(passengers, sorted_passengers, numPassengers);
}

void knuthShuffle(passenger *passengers, int start, int end) {
    for (int i = start; i < end; i++) {
        swap(passengers, randIndex(i, end), i);
    }
}

int randIndex(int i, int end) {
    return (rand() % (end - i)) + i;
}

void swap(passenger *passengers, int iA, int iB) {
    passenger temp = passengers[iA];
    passengers[iA] = passengers[iB];
    passengers[iB] = temp;
}

void steffenQue(passenger *passengers, passenger *sorted_passengers, int numPassengers)
{
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

int binarySearch(passenger *sortedPassengers, seatLetter seat, int row, int numPassengers)
{
    int left = 0, right = numPassengers, middle;
    int py, sy = seat < 4 ? seat + 6 : seat;
    passenger p;

    while (left < right){
        // Get middle
        middle = (left + right) * 0.5;
        p = sortedPassengers[middle];

        // If passenger row is greater than seeked Row
        if (p.seatPos.x > row)
            right = middle;
            // If passenger row is correct
        else if (p.seatPos.x == row)
        {
            py = p.seatPos.y < 4 ? p.seatPos.y + 6 : p.seatPos.y;
            // If passenger seat is greater than seeked seat
            if (py > sy)
                left = middle + 1;
                // If the right seat and row have been found
            else if (py == sy)
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
    int r = a->seatPos.x - b->seatPos.x;
    if(r != 0)
        return r;

    // Place in row A (A B C, F E D)
    int ay = a->seatPos.y < 4 ? a->seatPos.y + 6 : a->seatPos.y;
    int by = b->seatPos.y < 4 ? b->seatPos.y + 6 : b->seatPos.y;
    return by - ay;
}

/*
 * Dummy stuff :D
 */

void printPassenger(passenger passengers[189])
{
    for (int i = 0; i < 189; ++i)
    {
        printf("%3d row: %2d, seat %c\n", i, passengers[i].seatPos.x, GetSeatName((seatLetter) passengers[i].seatPos.y));
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
    return '\0';
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
