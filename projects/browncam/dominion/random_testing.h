#ifndef RANDOM_TESTING_H
#define RANDOM_TESTING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"

/*****************************************
        Random Tester Setup
*****************************************/


// global constants 
#define NUM_TESTS 100
#define MINCARDS 3

//function prototypes 
int randIntGenerator(int low, int high);
void randStateGenerator(struct gameState *state);

//holds test failures for a given test card
struct failedTests {
    int t1;
    int t2;
    int t3;
    int t4;
};


#endif