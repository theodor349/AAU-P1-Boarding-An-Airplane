#include "..\Header.h"
#include <time.h>
#include <unistd.h>

#define NUM_OF_SEATS_IN_ROW 6

void GenerateTestData(char *name, int passengerAmount, int luggagePercent);

int main(void)
{
    char* fileName = calloc(32, 1);
    int numPassengers = 189, luggagePercent;
    int stepSize = 1, multiples = 10;

    chdir("..");
    chdir("..");
    if(chdir("\TestData") != 0)
        printf("Something Went Bad with the directories \n");

    int check = 100 * multiples + 1;
    int fileNum = 0;
    for (int i = 0; i < check; i += stepSize, fileNum++)
    {
        sprintf(fileName, "LuggagePercent_%d.txt", fileNum);
        luggagePercent = i % 101;
        GenerateTestData(fileName, numPassengers, luggagePercent);
    }

    return 0;
}

void GenerateTestData(char *name, int passengerAmount, int luggagePercent)
{
    int i = 0, j = 0, determineChance = 0, rowNum = 1, hasLuggage = 0;
    int numLuggage = 0;
    char seatNum[NUM_OF_SEATS_IN_ROW] = {'A','B','C','D','E','F'};
    srand(time(NULL));

    FILE *passengerFile = fopen(name, "w");
    if (passengerFile == NULL) {
        printf("FILE NOT FOUND\n");
        exit(0);
    }

    for (i = 1; i < passengerAmount + 1; i++) {
        determineChance = rand() % 100 + 1;
        if (determineChance > luggagePercent) {
            hasLuggage = 0;
        }
        else {
            hasLuggage = 1;
            numLuggage++;
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

    fprintf(passengerFile, "L%d", numLuggage);

    fclose(passengerFile);
    int p = (numLuggage / (float)passengerAmount) * 100;
    //printf("Made Data: %s with %d luggage\n", name, p);
}

