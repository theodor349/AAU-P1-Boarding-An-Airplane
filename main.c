#include "Header.h"
#define BOARDINGALGORITHMS 3

int main (void){
    // Boarding procedure Times    
    boardingCalculation boardingCalculations[BOARDINGALGORITHMS];

    // Initial setup
    FILE *passengerSource = fopen("passengerText.txt", "r");
    passenger *pArray = gather(passengerSource);
    int pAmount = getPassengerAmount(passengerSource);

    // For each Boarding procedure 
    for (int i = 0; i < BOARDINGALGORITHMS; i++) {
        // Order Passengers
        QueuePassengers(pArray, pAmount, (boardingProcedure) i);

        // Calculate Boarding Time
        boardingCalculations[i].time = runSimulation(pArray, pAmount);
        boardingCalculations[i].procedure = i;
    }

    // Sort the Boarding Times
    qsort(boardingCalculations, BOARDINGALGORITHMS, sizeof(boardingCalculation), (compfn)timeCmp);

    // Print the results
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
            case BackToFront:
                printf("%-30s | ", "Back-to-front boarding time");
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
