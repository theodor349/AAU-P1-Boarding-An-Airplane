#include "..\Header.h"
#include <unistd.h>

#define BOARDINGALGORITHMS 3

int RunProgram();
int RunTests();
void GetBoardingTimes(FILE *passengerSource, boardingCalculation boardingCalculations[BOARDINGALGORITHMS]);
FILE *GetFilePointer(int index);
int getLuggageAmount(FILE *passengerSource);

void writeTestResults(int boardingTimes[][BOARDINGALGORITHMS][2]);

int main (void){
    int result;
    int input = 1;
    if(1 == 0)
    {
        printf("0 = Tests, 1 = Program\n");
        scanf(" %d", &input);
    }
    else
        input = 0;

    if(input > 0)
        result = RunProgram();
    else
        result = RunTests();

    return result;
}

int RunTests()
{
    // Navigate to Test dir
    chdir("..");
    chdir("..");
    if(chdir("\TestData") != 0)
        printf("Something Went Bad with the directories \n");

    // Boarding procedure Times
    boardingCalculation boardingCalculations[BOARDINGALGORITHMS];
    int index = 0, numPassengers, numLuggage, position;
    int tBoardingTimes[101][BOARDINGALGORITHMS][2];
    // Reset Array
    for (int position = 0; position < 101; ++position)
    {
        for (int i = 0; i < BOARDINGALGORITHMS; ++i)
        {
            tBoardingTimes[position][i][0] = 0;
            tBoardingTimes[position][i][1] = 0;
        }
    }

    // Get filename;
    FILE *passengerSource = GetFilePointer(index);

    // Run through all tests
    while (passengerSource != NULL)
    {
        GetBoardingTimes(passengerSource, boardingCalculations);

        numPassengers = getPassengerAmount(passengerSource);
        numLuggage = getLuggageAmount(passengerSource);
        position = (numLuggage / (float)numPassengers) * 100;

        for (int i = 0; i < BOARDINGALGORITHMS; ++i)
        {
            tBoardingTimes[position][i][0] = tBoardingTimes[position][i][0] + boardingCalculations[i].time;
            tBoardingTimes[position][i][1] = tBoardingTimes[position][i][1] + 1;
        }

        index++;
        passengerSource = GetFilePointer(index);
    }

    /*
     * MAKE OUTPUT
     */

    if(chdir("\Results") != 0)
        printf("Something Went Bad with the directories \n");
    FILE *outputFile = fopen("Results.csv", "w");

    for (int i = 0; i < BOARDINGALGORITHMS; ++i)
    {
        fprintf(outputFile, "\n")
        switch(i)
        {
            case Random:
                fprintf(outputFile, "%s", "Random\n");
                break;
            case SteffenModified:
                fprintf(outputFile, "%s", "Steffen Modified\n");
                break;
            case BackToFront:
                fprintf(outputFile, "%s", "Back to Front\n");
                break;
            default:
                fprintf(outputFile, "%s", "Error\n");
                break;
        }
        for (int position = 0; position < 101; ++position)
        {
            if(tBoardingTimes[position][i][1] > 0)
            {
                int time = tBoardingTimes[position][i][0] / tBoardingTimes[position][i][1];
                if(position == 100)
                    fprintf(outputFile, "%d, ", 1);
                else
                    fprintf(outputFile, "0.%d, ", position);
                fprintf(outputFile, "%d\n", time);
            }
        }
    }
    fclose(outputFile);

    printf("Read %d files\n", index);
    return EXIT_SUCCESS;
}

void writeTestResults(int boardingTimes[][BOARDINGALGORITHMS][2])
{

}

int getLuggageAmount(FILE *passengerSource)
{
    int amount = 0;
    char* line = calloc(256, 1);
    rewind(passengerSource);

    if (passengerSource != NULL) {
        while (fgets(line, 256, passengerSource) != NULL)
        {
            if(line[0] == 'L')
                sscanf(line, "L%d", &amount);
        }
    }
    return amount;
}

FILE *GetFilePointer(int index)
{
    char* fileName = calloc(32, 1);
    sprintf(fileName, "LuggagePercent_%d.txt", index);
    return  fopen(fileName, "r");
}


int RunProgram()
{
    // Boarding procedure Times
    boardingCalculation boardingCalculations[BOARDINGALGORITHMS];

    // Initial setup
    FILE *passengerSource = fopen("passengerText.txt", "r");
    GetBoardingTimes(passengerSource, boardingCalculations);

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

        printf("%-4d seconds \n", boardingCalculations[i].time);
    }

    fclose(passengerSource);

    return EXIT_SUCCESS;
}

void GetBoardingTimes(FILE *passengerSource, boardingCalculation boardingCalculations[BOARDINGALGORITHMS])
{

    passenger *pArray = gather(passengerSource);
    int pAmount = getPassengerAmount(passengerSource);

    // For each Boarding procedure
    for (int i = 0; i < BOARDINGALGORITHMS; i++) {
        int times = i < 2 ? 100 : 1;
        int tValue = 0;

        for (int j = 0; j < times; ++j)
        {
            // Order Passengers
            QueuePassengers(pArray, pAmount, (boardingProcedure) i);
            tValue += runSimulation(pArray, pAmount);
        }
        // Calculate Boarding Time
        boardingCalculations[i].time = tValue / times;
        boardingCalculations[i].procedure = i;

    }
    free(pArray);
}
