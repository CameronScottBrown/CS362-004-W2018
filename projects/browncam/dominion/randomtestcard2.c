/*
    CS 362 - Winter 2018
    Assignment 4
    
    RANDOMTESTCARD2.C
    
    This program contains a random test generator for the Smithy card in Dominion.
    ===================
    Card Code:
    ===================
            //+3 Cards
            for (i = 0; i < 3; i++) //unbugged
            {
              drawCard(currentPlayer, state);
            }

          //discard card from hand
          discardCard(handPos, currentPlayer, state, 0);
          return 0; 
    
    ===================
    Smithy Parameters (Inputs): state, currentPlayer, handPos
    ===================
    
    ===================
    Smithy Expectations (from Assignment 3):
    ===================
*       TEST 1 - increase the player's hand by 2 (+3 gained, -1 played)
*       TEST 2 - not add any actions to turn (card is terminal)
*       TEST 3 - cards gained from that player's supply
*       TEST 4 - gameState should not change for any other players


*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "random_testing.h"


//function prototype
void testSmithy(struct gameState *pre, struct failedTests *f);


/*****************************************
    MAIN FUNCTION -- Runs tests, prints results
 *****************************************/
int main() {
    
    // random seed
    srand(time(NULL));
    
    // initiate testing
    printf("SMITHY CARD: Running %d tests... \n", NUM_TESTS);
    
    // counter
    int i;
    
    // initialize empty struct for failed tests
    struct failedTests f = {0};
    
    // implement tests by creating and filling random game states and testing the smithy card
    for (i = 0; i < NUM_TESTS; i++) {
        struct gameState state;
        randStateGenerator(&state);
        testSmithy(&state, &f);
    }

    // tests are completed
    printf("SMITHY CARD: %d tests completed.\n", NUM_TESTS);
    
    
    // printing results
    if (f.t1 + f.t2 + f.t3 + f.t4 > 0) {
        printf("\nOne or more of the tests for SMITHY have failed.\n");
    }
    else {
        printf("\nAll SMITHY tests have passed\n");
    }
	
    // printing specific failure rates for each test
    printf("\n========== FAILURE RATES ==========\n");
    
    // prints each failure rate as a 2 point float based on number of tests ran
    printf("Test 1: %.2f%%\n", f.t1 * 1.0 / NUM_TESTS * 100);
    printf("Test 2: %.2f%%\n", f.t2 * 1.0 / NUM_TESTS * 100);
    printf("Test 3: %.2f%%\n", f.t3 * 1.0 / NUM_TESTS * 100);
    printf("Test 4: %.2f%%\n", f.t4 * 1.0 / NUM_TESTS * 100);
    
    return 0;
}


/*****************************************
    testSmithy(pre-test game state) - takes a game state, 
    applies random variables, copies the state, and tests the pre state
*****************************************/
void testSmithy(struct gameState *pre, struct failedTests *f) {
    
    // randomized input variables for the cardEffect function
    
    int handPos;  // ranges from 0 to the handCount of currentPlayer
    int choice1, choice2, choice3;  // ranges from 0 to 26 based on card value
    int bonus;  // ranges from 0 to the max deck count
    
    // assignments for testing
    int currentPlayer = pre->whoseTurn;
    struct gameState post; // struct for testing card effect
    int i;

    handPos = randIntGenerator(0, pre->handCount[currentPlayer]);
    pre->hand[currentPlayer][handPos] = smithy;

    // copy game state over
    memcpy(&post, pre, sizeof(struct gameState));

    bonus = randIntGenerator(0, MAX_DECK);
    choice1 = randIntGenerator(curse, treasure_map);
    choice2 = randIntGenerator(curse, treasure_map);
    choice3 = randIntGenerator(curse, treasure_map);

    // implements the smithy card effect
    cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus); 

    /*************************
     Pre and Post Comparisons
    **************************/
    
    /**********************
    *   TEST 1 - increase the player's hand by 2 (+3 gained, -1 played)
    ***********************/
    if (pre->handCount[currentPlayer] + 2 != post.handCount[currentPlayer]) {
        f->t1++;
    }

    /**********************
    *   TEST 2 - not add any actions to turn (card is terminal)
    ***********************/
    if (pre->numActions != post.numActions){
        f->t2++;
    }

    /**********************
    *   TEST 3 - cards gained from that player's supply
    ***********************/
    if (pre->deckCount[currentPlayer] - 1 != post.deckCount[currentPlayer]) {
        f->t3++;
    }

    /**********************
    *   TEST 4 - gameState should not change for any other players
    ***********************/
    for (i = 0; i < pre->numPlayers; i++) {
        if (i == currentPlayer) { //skips current player
            continue;
        } 
        else { //checks other player pre and post decks
            if (pre->deckCount[i] != post.deckCount[i] || pre->handCount[i] != post.handCount[i] || pre->discardCount[i] != post.discardCount[i]) { 
                    f->t4++; 
            }
        }
    }

}

