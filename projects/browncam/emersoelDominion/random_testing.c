#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion_helpers.h"
#include "rngs.h"
#include "random_testing.h"


/*****************************************
        Random Tester Setup
*****************************************/
/***************************************** 
    randIntGenerator(low, high) - returns a random integer within given range
******************************************/
int randIntGenerator(int low, int high) {
    double r = rand();
    return (int)(low + r * (high - low) / (double)RAND_MAX); // found on github, generates a casted rand int
}

/*****************************************
    randStateGenerator(game state) - takes an empty game state struct and assigns random 'trash' data
******************************************/
void randStateGenerator(struct gameState *state) {
    
    // set the number of players and the current player
    int numPlayers = randIntGenerator(2, MAX_PLAYERS);
    int currentPlayer = randIntGenerator(0, numPlayers);

    int i;
    for (i = 0; i < sizeof(struct gameState); i++) {
	   // fill game state
        ((char*)state)[i] = floor(Random() * 256);
    }

    // random assignment of game state variables
    state->deckCount[currentPlayer] = randIntGenerator(MINCARDS, MAX_DECK);
    state->discardCount[currentPlayer] = randIntGenerator(0, MAX_DECK - state->deckCount[currentPlayer]);
    state->handCount[currentPlayer] = randIntGenerator(0, MAX_DECK - state->deckCount[currentPlayer] - state->discardCount[currentPlayer]);
    state->playedCardCount = 0;
    state->numPlayers = numPlayers;
    state->whoseTurn = currentPlayer;

    
    // random card assignment for current player
    
    //random deck
    for (i = 0; i < state->deckCount[currentPlayer]; i++){
        state->deck[currentPlayer][i] = randIntGenerator(curse, treasure_map);
    }
	
    //random discard pile
    for (i = 0; i < state->discardCount[currentPlayer]; i++){
        state->discard[currentPlayer][i] = randIntGenerator(curse, treasure_map);
    }
	
    //random hand
    for (i = 0; i < state->handCount[currentPlayer]; i++){
        state->hand[currentPlayer][i] = randIntGenerator(curse, treasure_map);
    }
    
}


