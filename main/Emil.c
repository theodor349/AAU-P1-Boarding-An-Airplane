#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_SEATS 189

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
enum boardingProcedure{
    Random,
    SteffenModified
} procedure;

typedef
struct point {
    float x, y;
} point;

typedef
struct passenger {
    point currPos;
    point seatPos;
    state currState;
    int ticksToWait;
    bool hasLuggage;
} passenger;

int main (void) {
    FILE *testFile;
    int ch;
    int i = 0;
    passenger passengers[MAX_SEATS];

    testFile = fopen("passengertest.txt", "r");

    if (testFile != NULL) {
        while ((ch = fgetc(testFile)) != EOF && (ch = fgetc(testFile)) != 'A') {
                passengers[i].seatPos.x = ch;
                i++;
        }
    }
// for testing purposes
    printf("%lf\n%lf\n%lf\n%lf\n%lf\n", passengers[0].seatPos.x, passengers[1].seatPos.x, passengers[2].seatPos.x, passengers[3].seatPos.x, passengers[4].seatPos.x);

    return 0;
}
