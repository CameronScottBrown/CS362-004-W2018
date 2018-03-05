/*
*   Cameron Brown
*   Unit Test 1 -- gainCard ()
*   
*   function params:    supply pos, game state, destination flag, player
*   function action:    updates the destination card count
*           
*   TESTS -- gain card to various destinations
*           gold supply, deck, player hand, discard pile
*         -- check that decreasing gold during a gainCard works
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
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 500;
    struct gameState state;

    printf("===== UNIT TEST 1 -- gainCard() =====\n");
    memset(&state,23,sizeof(struct gameState));
    initializeGame(2, k, seed, &state);

    printf("\nGold supply pile is empty\n");
    state.supplyCount[gold] = 0;
    customAssert(gainCard(gold,&state,0,0),-1);
    state.supplyCount[gold] = 30;

    printf("\nAdd card to deck\n");
    int deckCount = state.deckCount[0];
    gainCard(gold,&state,1,0);
    customAssert(deckCount+1,state.deckCount[0]);

    printf("\nAdd card to hand\n");
    int handCount = state.handCount[0];
    gainCard(gold,&state,2,0);
    customAssert(handCount+1,state.handCount[0]);

    printf("\nAdd card to discard pile\n");
    int discardCount = state.discardCount[0];
    gainCard(gold,&state,0,0);
    customAssert(discardCount+1,state.discardCount[0]);

    printf("\nDecrease gold supply\n");
    int goldSupply = state.supplyCount[gold];
    gainCard(gold,&state,0,0);
    customAssert(goldSupply-1,state.supplyCount[gold]);

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