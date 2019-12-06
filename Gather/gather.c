#include "..\Header.h"

#define MAX_SEATS 189
#define LENGTH 10

passenger* gather(FILE *passengerSource) {
    passenger *passengerArray;
    int passengerAmount = 0;

    passengerAmount = getPassengerAmount(passengerSource);

    passengerArray = calloc(passengerAmount, sizeof(passenger));
    readFile(passengerArray, passengerSource, passengerAmount);

    // printf("x = %d luggage(0, 1) = %d %d\n", passengerArray[10].seatPos.x, passengerArray[10].hasLuggage, passengerArray[10].seatPos.y);
    // printf("passengerAmount = %d\n", passengerAmount);
    return passengerArray;
}

int getPassengerAmount(FILE *passengerSource) {
    int ch, passengerAmount = 0;
    rewind(passengerSource);

    if (passengerSource != NULL) {
        while ((ch = fgetc(passengerSource)) != EOF) {
            if (ch == '\n') {
                passengerAmount += 1;
            }
        }
    }
    return passengerAmount;
}

void readFile(passenger *passengerArray, FILE *passengerSource, int passengerAmount) {
    char tempChar = 0;
    int i = 0;

    rewind(passengerSource);

    if (passengerSource != NULL) {
        for (i = 0; i < passengerAmount; i++) {
            fscanf(passengerSource, " %d %c %d", &passengerArray[i].seatPos.x, &tempChar, &passengerArray[i].hasLuggage);

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
