/*
*   Card Test 3 - Village
*
*   village card expectations:
*       TEST 1 - player's hand does not change overall (+1 gained, -1 played)
*       TEST 2 - increase player's actions by 2
*       TEST 3 - card is gained from player's own pile
*       TEST 4 - kingdom and victory piles should not change
*       TEST 5 - gameState should not change for any other players 
*
*   We will use a Test State and a Control State for the games.
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

int main(){
    int i;
    int playerCount = 2;
    int player0 = 0;
    int player1 = 1;
    
    int handPos = 0,
        choice1 = 0, 
        choice2 = 0, 
        choice3 = 0,
        bonus = 0;

    // Kingdom Cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 500;
    
    printf("CARD TEST 3 - VILLAGE\n");
    
    /***********************************************
    *   SETUP TEST AND CONTROL STATES
    ***********************************************/
    struct gameState testState, controlState;
    memset(&testState,23,sizeof(struct gameState));
    memset(&controlState,23,sizeof(struct gameState));

    // create a state
    initializeGame(playerCount, k, seed, &testState);

    // preserve it for later comparison
    memcpy(&controlState, &testState, sizeof(struct gameState));
    
    /***********************************************
    * APPLY THE VILLAGE CARD
    ***********************************************/
    
    // applies village card
    cardEffect(village, choice1, choice2, choice3, &testState, handPos, &bonus);

    
    /***********************************************
    * TEST 1 - player's hand increases by 1
    ***********************************************/
    printf("\nTEST 1: Player's hand increases by 0 overall (+1 and -1)\n");
    customAssert(testState.handCount[player0],controlState.handCount[player0]);

    
    /***********************************************
    * TEST 2 - player's actions increase by 2
    ***********************************************/
    printf("\nTEST 2: Player's actions increase by 2\n");
    customAssert(testState.numActions,controlState.numActions+2);
    
    
    /***********************************************
    * TEST 3 - player gains card from own supply
    ***********************************************/   
    printf("\nTEST 3: Player gains card from own supply\n");
    customAssert(testState.deckCount[player0],controlState.deckCount[player0]-1);


    /***********************************************
    * TEST 4 - Kindgom and Victory Piles unchanged
    ***********************************************/
    printf("\nTEST 4a: Checking Kingdom Card Piles\n");
    
    for (i = 0; i < 10; i++) {
        printf("testing kingdom card...\n");
        customAssert(testState.supplyCount[k[i]],controlState.supplyCount[k[i]]);
    }

    printf("\nTEST 4b: Checking Victory Card Piles\n");
    printf("Checking Province Pile\n");
    customAssert(testState.supplyCount[province],controlState.supplyCount[province]);
    printf("Checking Duchy Pile\n");
    customAssert(testState.supplyCount[duchy],controlState.supplyCount[duchy]);
    printf("Checking Estate Pile\n");
    customAssert(testState.supplyCount[estate],controlState.supplyCount[estate]);

    /***********************************************
    * TEST 5 - gameState should not change for any other players
    ***********************************************/
    printf("\nTEST 5: Checking Other Player's Game State\n");
    printf("Checking Hand Count\n");
    customAssert(testState.handCount[player1],controlState.handCount[player1]);
    printf("Checking Deck Count\n");
    customAssert(testState.deckCount[player1],controlState.deckCount[player1]);



    if (numFails) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",numFails);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}