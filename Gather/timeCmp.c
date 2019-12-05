#include "..\Header.h"



int timeCmp (const void *a, const void *b){

    return (*(int*)a->time - *(int*)b->time);
}
