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
    readFile(passengerArray, testFile, passengerAmount);

    printf("x = %d luggage(0, 1) = %d %d\n", passengerArray[10].seatPos.x, passengerArray[10].hasLuggage, passengerArray[10].seatPos.y);
    printf("passengerAmount = %d\n", passengerAmount);
    return 0;
}

int getPassengerAmount(FILE *testFile) {
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

void readFile(passenger *passengerArray, FILE *testFile, int passengerAmount) {
    char tempChar = 0;
    int i = 0;

    rewind(testFile);

    if (testFile != NULL) {
        for (i = 0; i < passengerAmount; i++) {
            fscanf(testFile, " %d %c %d", &passengerArray[i].seatPos.x, &tempChar, &passengerArray[i].hasLuggage);

            switch (tempChar) {
                case 'A':
                    passengerArray[i].seatPos.y = A;
                    break;
                case 'B':
                    passengerArray[i].seatPos.y = B;
                    break;
                case 'C':
                    passengerArray[i].seatPos.y = C;
                    break;
                case 'D':
                    passengerArray[i].seatPos.y = D;
                    break;
                case 'E':
                    passengerArray[i].seatPos.y = E;
                    break;
                case 'F':
                    passengerArray[i].seatPos.y = F;
                    break;
            }
        }
    }
}
