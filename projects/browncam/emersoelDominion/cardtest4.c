/*
*   Card Test 4 - Mine
*
*    mine card expectations:
*       - TEST 1: hand count should not change overall (-1 treasure, +1 treasure)
*       - TEST 2: player's treasure card count should be equal
*       - TEST 3: player's treasure value should be >= original treasure
*       - TEST 4: player's actions remain unchanged
*       - TEST 5: kingdom and victory piles should remain unchanged
*       - TEST 6: gameState should not change for any other players
*
*       We will use a Test State and a Control State for the games.
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
    
    int testTreasureValue = 0,
        controlTreasureValue = 0;
    
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
    
    printf("CARD TEST 4 - MINE\n");
    
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
    * APPLY THE MINE CARD
    ***********************************************/

    //applies the mine card
    cardEffect(mine, choice1, choice2, choice3, &testState, handPos, &bonus);

    /***********************************************
    * TEST 1 - hand count should not change overall
    ***********************************************/
    printf("\nTEST 1: Player hand count unchanged overall\n");
    customAssert(testState.handCount[player0],controlState.handCount[player0]);
    
    
    /***********************************************
    * TEST 2 - player's treasure card count should be equal
    ***********************************************/

    for (i = 0; i < testState.handCount[player0]; i++) {
        card = testState.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            testTreasure++;
        }
    }

    // checks default treasure count
    for (i = 0; i < controlState.handCount[player0]; i++) {
        card = controlState.hand[player0][i];
        if (card == copper || card == silver || card == gold) {
            controlTreasure++;
        }
    }

    printf("\nTEST 2: Player has same number of treasure cards\n");
    customAssert(controlTreasure,testTreasure);
    
   /***********************************************
    * TEST 3 - player's treasure value should be >= original treasure
    ***********************************************/
    for (i = 0; i < testState.handCount[player0]; i++) {
    card = testState.hand[player0][i];
        if (card == copper){
            testTreasureValue++;
        } else if (card == silver){
            testTreasureValue = testTreasureValue+2;
        } else { //it's gold
            testTreasureValue = testTreasureValue+3;
        }
        
    }

    // checks control treasure value
    for (i = 0; i < controlState.handCount[player0]; i++) {
        card = controlState.hand[player0][i];
        if (card == copper){
            controlTreasureValue++;
        } else if (card == silver){
            controlTreasureValue = controlTreasureValue+2;
        } else { //it's gold
            controlTreasureValue = controlTreasureValue+3;
        }
    }

    printf("\nTEST 3: Player has greater or equal treasure value\n");
    if(controlTreasureValue <= testTreasureValue){
        printf("Test: PASSED\n");
        numPasses++;
    } else {
        printf("Test: FAILED\n");
        numFails++;
    }
    
    /***********************************************
    * TEST 4 - no actions added to player turn
    ***********************************************/
    printf("\nTEST 4: Player actions remain unchanged\n");
    customAssert(testState.numActions, controlState.numActions);
    
    
    /***********************************************
    * TEST 5 - Kindgom and Victory Piles unchanged
    ***********************************************/
    printf("\nTEST 6a: Checking Kingdom Card Piles\n");
    
    for (i = 0; i < 10; i++) {
        printf("testing kingdom card...\n");
        customAssert(testState.supplyCount[k[i]],controlState.supplyCount[k[i]]);
    }

    printf("\nTEST 6b: Checking Victory Card Piles\n");
    printf("Checking Province Pile\n");
    customAssert(testState.supplyCount[province],controlState.supplyCount[province]);
    printf("Checking Duchy Pile\n");
    customAssert(testState.supplyCount[duchy],controlState.supplyCount[duchy]);
    printf("Checking Estate Pile\n");
    customAssert(testState.supplyCount[estate],controlState.supplyCount[estate]);

    /***********************************************
    * TEST 6 - gameState should not change for any other players
    ***********************************************/
    printf("\nTEST 7: Checking Other Player's Game State\n");
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