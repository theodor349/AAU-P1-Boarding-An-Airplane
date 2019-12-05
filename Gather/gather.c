#include "..\Header.h"

#define MAX_SEATS 189
#define LENGTH 10



int gather(void) {
    passenger *passengerArray;
    FILE *testFile;
    int passengerAmount = 0;

    testFile = fopen("passengertest.txt", "r");
    passengerAmount = getPassengerAmount(testFile);

// remeber to free
    passengerArray = calloc(passengerAmount, sizeof(passenger));
    readFile(passengerArray, testFile);


    return 0;
}

int getPassengerAmount(FILE *testFile){
    int ch, passengerAmount = 0;

    if (testFile != NULL) {
        while ((ch = fgetc(testFile)) != EOF) {
            if (ch == '\n') {
                passengerAmount += 1;
            }
        }
    }
    return passengerAmount;
// for testing purposes
    // printf("%lf\n%lf\n%lf\n%lf\n%lf\n", passengers[0].seatPos.x, passengers[1].seatPos.x, passengers[2].seatPos.x, passengers[3].seatPos.x, passengers[4].seatPos.x);


/*
    if (fgets(line, LENGTH, testFile) != NULL) {
            sscanf(line, " %d", &q);
    }

    printf("%d\n", q);
*/
}

void readFile(passenger *passengerArray, FILE *testFile) {
    if (testFile != NULL) {
        
    }

}
