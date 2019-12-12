#include "..\..\Header.h"

void stateSeating(passenger *pArr, int pArrSize, int i) {
	// Is the passenger at the intended seat?
	if(pArr[i].currPos.y == pArr[i].seatPos.y) {
		// Then set the passenger to Idle
		pArr[i].currState = Idle;
		return;
	}

	if(abs(pArr[i].seatPos.y) > 1) {
		// Get number of passengers blocking the way to the seat
		int O = countPassengersInRow(pArr, pArrSize, i);
		if(O > 0) {
	        // Get seat position of closes passenger
			int Sp = abs(pArr[getClosestToAisle(pArr, pArrSize, i)].seatPos.y);
			// Set time to wait
			pArr[i].ticksToWait = (2*(O + Sp) - (Sp - 1)) - 1;
		}
	}

	// Set the passenger to be at the intented seat
    pArr[i].currPos.y = pArr[i].seatPos.y;
}

int countPassengersInRow(passenger *pArr, int pArrSize, int pI) {
	int n = 0;
	// For each passenger
	for(int i = 0; i < pArrSize; i++) {
		// If the passenger is idle(seated) and at the correct row
		if(pArr[i].currState == Idle && pArr[i].currPos.x == pArr[pI].currPos.x) {
			// If the seated passenger is blocking the way (Closer to the aisle than the destination seat)
			if((pArr[pI].seatPos.y > 0 && pArr[i].seatPos.y > 0) ||
			   (pArr[pI].seatPos.y < 0 && pArr[i].seatPos.y < 0))
                n++;
		}
	}
	return n;
}

int getClosestToAisle(passenger *pArr, int pArrSize, int pI) {
	int closestI, dist = 999;

	// For each passenger
	for(int i = 0; i < pArrSize; i++) {
		// If the passenger is idle(seated) and at the correct row
		if(pArr[i].currState == Idle && pArr[i].currPos.x == pArr[pI].currPos.x) {
			// If the seated passenger is blocking the way (Closer to the aisle than the destination seat)
			if((pArr[pI].seatPos.y > 0 && pArr[i].seatPos.y > 0) ||
			   (pArr[pI].seatPos.y < 0 && pArr[i].seatPos.y < 0)) {
			   	// Is the distance to the passenger less than the current distance?
				if(abs(pArr[i].seatPos.y) < dist) {
					// Set dist
					dist = abs(pArr[i].seatPos.y);
					// Set closest Passenger
					closestI = i;
				}
			}
		}
	}
	return closestI;
}
