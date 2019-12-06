#include "..\Header.h"

#define BOARDINGALGORITHMS 2

int main (void){

    boardingCalculation boardingCalculations[BOARDINGALGORITHMS];

    FILE *passengerSource = fopen("passengerText.txt", "r");
    passenger *pArray = gather(passengerSource);
    int pAmount = getPassengerAmount(passengerSource);

    for (int i = 0; i < BOARDINGALGORITHMS; i++ ){
        QueuePassengers(pArray, pAmount, (boardingProcedure) i);
        boardingCalculations[i].time = runSimulation(pArray, pAmount);
        boardingCalculations[i].procedure = i;
    }

    qsort(boardingCalculations, BOARDINGALGORITHMS, sizeof(boardingCalculation), (compfn)timeCmp);

    for(int i = 0; i < BOARDINGALGORITHMS; i++)
    {
        switch(boardingCalculations[i].procedure)
        {
            case Random:
                printf("%-30s | ", "Random boarding time");
                break;
            case SteffenModified:
                printf("%-30s | ", "Steffen modified boarding time");
                break;
            default:
                printf("error parsing boarding procedure: ");
                break;
        }

        printf("%-4d seconds \n", boardingCalculations[i]);
    }

    free(pArray);
    fclose(passengerSource);

    return EXIT_SUCCESS;
}
