#include "..\Header.h"

#define MAX_SEATS 189
#define LENGTH 10

void readinput(passenger *passengers);
int gather(void);

int gather(void) {
    int p = 0;
    passenger *passengers;
    passengers = calloc(p, sizeof(passenger));
    readinput(passengers);


    return 0;
}

void readinput(passenger *passengers){
    FILE *testFile;
    int q;
    char line[LENGTH];


    testFile = fopen("passengertest.txt", "r");

    if (fgets(line, LENGTH, testFile) != NULL) {
            sscanf(line, " %d", &q);
    }

    printf("%d\n", q);

    /*if (testFile != NULL) {
        while ((ch = fgetc(testFile)) != EOF && (ch = fgetc(testFile)) != 'A') {
                passengers[i].seatPos.x = ch;
                i++;
        }
    }
// for testing purposes
    printf("%lf\n%lf\n%lf\n%lf\n%lf\n", passengers[0].seatPos.x, passengers[1].seatPos.x, passengers[2].seatPos.x, passengers[3].seatPos.x, passengers[4].seatPos.x);
    */
}
