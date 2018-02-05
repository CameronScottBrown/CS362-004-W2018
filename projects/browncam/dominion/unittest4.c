/*
*   Cameron Brown
*   Unit Test 4 -- isGameOver()
*
*   function params:    game state
*   function action:    checks province cards and 3 supply piles 
*                           and returns 1 if empty
*
*   TESTS -- province deck is empty
*         -- 3 empty supply decks
*         -- game not over (decks not empty)
*
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// counter for fails + passes
int numFails = 0;
int numPasses = 0;


// function to check if two ints are equal or not
void customAssert(int a, int b) {
    if (a == b) {
        printf("Test: PASSED\n");
        numPasses++;
    }
    else {
        printf("Test: FAILED\n");
        numFails++;
    }
}

int main () {
    int playerCount = 2;

    // kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 500;
    struct gameState state;

    printf("===== UNIT TEST 4 -- isGameOver() =====\n");

    memset(&state,23,sizeof(struct gameState));
    initializeGame(playerCount, k, seed, &state);

    state.supplyCount[province] = 0;

    printf("\nProvince deck empty\n");
    customAssert(isGameOver(&state),1);

    state.supplyCount[province] = 1;

    state.supplyCount[0] = 0;
    state.supplyCount[1] = 0;
    state.supplyCount[2] = 0;

    printf("\nThree supply piles empty\n");
    customAssert(isGameOver(&state),1);

    state.supplyCount[0] = 1;
    state.supplyCount[1] = 1;
    state.supplyCount[2] = 1;

    printf("\nProvince deck not empty\n");
    printf("\nSupply piles not empty\n");
    customAssert(isGameOver(&state),0);

    if (numFails) {
        printf("\nTEST FAILED\n");
        printf("\nPasses: %d\n",numPasses);
        printf("Fails: %d\n",numFails);
    }
    else {
        printf("\nTEST COMPLETED\n\n");
        printf("====================\n");
    }

    return 0;
}