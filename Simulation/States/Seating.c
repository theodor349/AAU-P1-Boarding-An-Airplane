#include "..\..\Header.h"

void countPassengersInWay(passenger *pArr, int pArrSize, int pI);
int getClosestToAisle(passenger *pArr, int pArrSize, int pI);

void stateSeating(passenger *pArr, int i) {

	int O = countPassengersInRow(pArr, sizeof(pArr) / sizeof(pArr[0]), i);
	int Sp = abs(pArr[getClosestToAisle(pArr, sizeof(pArr) / sizeof(pArr[0]), i)].seatPos.y);

    pArr[i].ticksToWait = 2*(O + Sp) - (Sp - 1);
}

void countPassengersInRow(passenger *pArr, int pArrSize, int pI) {
	int n = 0;
	for(int i = 0; i < pArrSize; i++) {
		if(pArr[i].isSeated && pArr[i].currPos.x == pArr[pI].seatPos.x) {
			if((pArr[pI].seatPos.y > 0 && pArr[i].seatPos.y > 0) ||
			   (pArr[pI].seatPos.y < 0 && pArr[i].seatPos.y < 0))
                n++;
		}
	}
	return n;
}

int getClosestToAisle(passenger *pArr, int pArrSize, int pI) {
	int closestI, dist = 999;
	for(int i = 0; i < pArrSize; i++) {
		if(pArr[i].isSeated && pArr[i].currPos.x == pArr[pI].seatPos.x) {
			if((pArr[pI].seatPos.y > 0 && pArr[i].seatPos.y > 0) ||
			   (pArr[pI].seatPos.y < 0 && pArr[i].seatPos.y < 0)) {
				if(abs(pArr[i].seatPos.y) < dist) {
					dist = abs(pArr[i].seatPos.y);
					closestI = i;
				}
			}
		}
	}
	return closestI;
}