/*
*   Card Test 2 - Adventurer
*
*   adventurer card expectations:
*       TEST 1 - draw cards until two treasure cards are drawn (+2 overall)
*       TEST 2 - player's treasure cards increases by 2
*       TEST 3 - not add any actions to turn (card is terminal)
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
    
    int testTreasure = 0,
        controlTreasure = 0;
    
    int playerCount = 2;
    int player0 = 0,
        player1 = 1;
    
    int card;
    
    int handPos = 0,
        choice1 = 0, 
        choice2 = 0, 
        choice3 = 0,
        bonus = 0;

    // Kingdom Cards
    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

    int seed = 500;
    
    printf("CARD TEST 2 - ADVENTURER\n");
    
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
    * APPLY THE ADVENTURER CARD
    ***********************************************/
    
    // applies adventurer card
    cardEffect(adventurer, choice1, choice2, choice3, &testState, handPos, &bonus);

    
    /***********************************************
    * TEST 1 - player gains 2 cards overall
    ***********************************************/
    printf("\nTEST 1: Player hand increased by 2 overall\n");
    customAssert(testState.handCount[player0],controlState.handCount[player0]+2);

    
    /***********************************************
    * TEST 2 - player's treasure cards increases by 2
    ***********************************************/
    for (i = 0; i < testState.handCount[player0]; i++) {
        card = testState.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            testTreasure++;
        }
    }

    // checks control treasure count
    for (i = 0; i < controlState.handCount[player0]; i++) {
        card = controlState.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            controlTreasure++;
        }
    }

    printf("\nTEST 2: Player gains +2 treasure\n");
    customAssert(controlTreasure+2,testTreasure);

    /***********************************************
    * TEST 3 - no actions added to player turn
    ***********************************************/
    printf("\nTEST 3: Player actions remain unchanged\n");
    customAssert(testState.numActions, controlState.numActions);
    
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

    if (numFails) {
        printf("\nTEST FAILED\n");
        printf("Fails: %d\n",numFails);
    }
    else {
        printf("\nTEST SUCCESSFULLY COMPLETED\n\n");
    }

    return 0;
}