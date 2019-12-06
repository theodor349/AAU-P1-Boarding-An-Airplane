#include "..\Header.h"

#define BOARDINGALGORITHMS 2

int main (void){

    boardingCalculation boardingCalculations[BOARDINGALGORITHMS];

    FILE *passengerSource = fopen("passengerText.txt", "r");
    passenger *pArray = gather(passengerSource);
    int pAmount = getPassengerAmount(passengerSource);

    for (int i = 0; i < BOARDINGALGORITHMS; i++ ){
        printf("\nNew Boarding Procedure: %d\n", i);
        QueuePassengers(pArray, pAmount, (boardingProcedure) i);
        boardingCalculations[i].time = runSimulation(pArray, pAmount);
        boardingCalculations[i].procedure = i;
        printf("Boarding procedure: %d finished in %d seconds\n", i, boardingCalculations[i].time);
    }

    qsort(boardingCalculations, BOARDINGALGORITHMS, sizeof(int), (compfn)timeCmp);

    printf("\nBoarding times in ascending order: \n");

    for(int i = 0; i < BOARDINGALGORITHMS; i++){

        switch(boardingCalculations[i].procedure){

            case Random:
                printf("Random boarding time: ");
                break;

            case SteffenModified:
                printf("Steffen modified boarding time: ");
                break;

            default:
                printf("error parsing boarding procedure: ");
                break;
        }

        printf("%-20d seconds \n", boardingCalculations[i]);
    }

    free(pArray);
    fclose(passengerSource);

    return EXIT_SUCCESS;
}
