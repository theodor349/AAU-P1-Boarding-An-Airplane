#include "Header.h"
#include <time.h>

#define NUM_OF_SEATS_IN_ROW 6
#define NUM_OF_ROWS 33

int main(void) {
    FILE *passengerFile = fopen("passengertext.txt", "w");
    int i = 0, j = 0, determineChance = 0, rowNum = 1, hasLuggage = 0, luggagePercent, passengerAmount = 0;
    char seatNum[NUM_OF_SEATS_IN_ROW] = {'A','B','C','D','E','F'};
    srand(time(NULL));

    if (passengerFile == NULL) {
        printf("FILE NOT FOUND\n");
        exit(0);
    }

    printf("Number of passengers to create whith given luggage %:\n");
    scanf(" %d %d", &passengerAmount, &luggagePercent);
    luggagePercent %= 100;

    for (i = 1; i < passengerAmount + 1; i++) {
        determineChance = rand() % 100 + 1;
        if (determineChance > luggagePercent) {
            hasLuggage = 0;
        }
        else {
            hasLuggage = 1;
        }
        if (rowNum != 13) {
            if (rowNum > 14) {
                rowNum--;
            }
            fprintf(passengerFile, "%d", rowNum);
            if (rowNum > 12) {
                rowNum++;
            }
            if (i > 1) {
                if (i % 6 == 0) {
                    rowNum++;
                }

            }
        }
        if (rowNum == 13) {
            rowNum++;
        }
        fprintf(passengerFile, "%c %d\n", seatNum[j], hasLuggage);
        j++;
        if (j >= NUM_OF_SEATS_IN_ROW) {
            j = 0;
        }
    }

fclose(passengerFile);
return 0;
}
