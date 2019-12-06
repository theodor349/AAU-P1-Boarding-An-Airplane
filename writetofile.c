#include "Header.h"
#include <time.h>

#define NUM_OF_SEATS_IN_ROW 6

int main(void) {
    FILE *passengerFile = fopen("passengertext.txt", "w");
    int i = 0, j = 0, determineChance = 0, rowNum = 0, hasLuggage = 0, passengerAmount = 0;
    char seatNum[NUM_OF_SEATS_IN_ROW] = {'A','B','C','D','E','F'};
    srand(time(NULL));

    if (passengerFile == NULL) {
        printf("FILE NOT FOUND\n");
        exit(0);
    }

    printf("Number of passengers to create:\n");
    scanf(" %d", &passengerAmount);

    for (i = 1; i < passengerAmount + 1; i++) {
        rowNum = i;
        determineChance = rand() % 100 + 1;
        if (determineChance > 90) {
            hasLuggage = 0;
        }
        else if (determineChance <= 90) {
            hasLuggage = 1;
        }
        fprintf(passengerFile, "%d%c %d\n", rowNum, seatNum[j], hasLuggage);
        j++;
        if (j > 5) {
            j = 0;
        }
    }

fclose(passengerFile);
return 0;
}
