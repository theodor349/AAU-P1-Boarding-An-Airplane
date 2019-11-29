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
    passenger passengers[MAX_SEATS];

    testFile = fopen("passengertest", "r");


    if (testFile != NULL) {
        while ((ch = fgetc(testFile)) != EOF) {
            /* code */
        }
    }

    return 0;
}
