#include "..\..\Header.h"

void stateSeating(passenger *pArr, int pArrSize, int i) {
	if(pArr[i].currPos.y == pArr[i].seatPos.y) {
		pArr[i].currState = Idle;
		return;
	}

	int O = countPassengersInRow(pArr, pArrSize, i);
	if(O > 0) {
		int Sp = abs(pArr[getClosestToAisle(pArr, pArrSize, i)].seatPos.y);
		pArr[i].ticksToWait = 2*(O + Sp) - (Sp - 1);
	}
    pArr[i].currPos.y = pArr[i].seatPos.y;
}

int countPassengersInRow(passenger *pArr, int pArrSize, int pI) {
	int n = 0;
	for(int i = 0; i < pArrSize; i++) {
		if(pArr[i].currState == Idle && pArr[i].currPos.x == pArr[pI].seatPos.x) {
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
		if(pArr[i].currState == Idle && pArr[i].currPos.x == pArr[pI].seatPos.x) {
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