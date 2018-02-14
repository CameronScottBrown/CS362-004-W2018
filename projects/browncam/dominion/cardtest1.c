/*
*   Card Test 1 - Smithy
*   
*   smithy card expectations:
*       TEST 1 - increase the player's hand by 2 (+3 gained, -1 played)
*       TEST 2 - not add any actions to turn (card is terminal)
*       TEST 3 - cards gained from that player's supply
*       TEST 4 - kingdom and victory card piles should not change
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
    

    printf("CARD TEST 1 - SMITHY\n");
   
    /***********************************************
    *   SETUP TEST AND CONTROL STATES
    ***********************************************/
    struct gameState testState, controlState;
    memset(&testState,23,sizeof(struct gameState));
    memset(&controlState,23,sizeof(struct gameState)); //will hold original state

    // create a game state
    initializeGame(playerCount, k, seed, &testState);

    // preserve the game state for later comparison
    memcpy(&controlState, &testState, sizeof(struct gameState));

    /***********************************************
    * APPLY THE SMITHY CARD
    ***********************************************/

    //applies the smithy card
    cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);

    
    /***********************************************
    * TEST 1 - increase the player's hand by 3, decrease by 1
    ***********************************************/
    printf("\nTEST 1: Player hand increased by 2 overall\n");
    customAssert(testState.handCount[player0],controlState.handCount[player0]+2);
    
    /***********************************************
    * TEST 2 - no actions added to player turn
    ***********************************************/
    printf("\nTEST 2: Player actions remain unchanged\n");
    customAssert(testState.numActions, controlState.numActions);
    
    /***********************************************
    * TEST 3 - cards gained from that player's supply
    ***********************************************/
    printf("\nTEST 3: Cards gained from player's own supply\n");
    customAssert(testState.deckCount[player0],controlState.deckCount[player0]-3);

    /***********************************************
    * TEST 4 - Kindgom and Victory Piles unchanged
    ***********************************************/
    printf("\nTEST 4: Checking Kingdom Card Piles\n");
    
    for (i = 0; i < 10; i++) {
        printf("testing kingdom card...\n");
        customAssert(testState.supplyCount[k[i]],controlState.supplyCount[k[i]]);
    }

    printf("\nTEST 4: Checking Victory Card Piles\n");
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

    // print number of failures
    if (numFails) {
        printf("\nTEST FAILED\n");
        printf("\nPasses: %d\n", numPasses);
        printf("Fails: %d\n", numFails);
    }
    else {
        // tests were passed!
        printf("\nCARD TEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}