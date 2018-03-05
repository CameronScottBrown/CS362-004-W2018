/*
*   Cameron Brown
*   Unit Test 2 -- shuffle ()
*
*   function params: player, game state
*   function action: shuffles a deck and stores the new deck in 
*                        each player's game state
*
*   TESTS:  -- check that shuffle returns -1 on an empty deck
*           -- make sure the deck contains same count before and after
*               for every player
*           -- compare a deck position before and after a shuffle
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
    int player = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};
    int seed = 500;
    struct gameState state;

    printf("===== UNIT TEST 2 -- shuffle()=====\n");
    memset(&state,23,sizeof(struct gameState));
    initializeGame(playerCount, k, seed, &state);

    state.deckCount[player] = 0;
    printf("\nPlayer's deck is empty\n");
    customAssert(shuffle(player,&state),-1);

    printf("\nPlayer deck count is 10 before and after shuffle\n");
    state.deckCount[player] = 10;
    shuffle(player,&state);
    customAssert(state.deckCount[player],10);

    printf("\nCards are shuffled\n");
    int pre_shuffle_card = state.deck[player][0];
    shuffle(player,&state);
    int post_shuffle_card = state.deck[player][0];
    if (pre_shuffle_card != post_shuffle_card) {
        customAssert(1,1);
    }
    else {
        customAssert(0,1);
    }

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