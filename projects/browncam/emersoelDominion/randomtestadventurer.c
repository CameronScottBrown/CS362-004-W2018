/*
    CS 362 - Winter 2018
    Assignment 4

    RANDOMTESTADVENTURER.C

    This program contains a random test generator for the Adventurer card in Dominion.
    ===================
    Card Code:
    ===================
    cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

        ... ...

    case adventurer:

        while(drawntreasure<2){ //unbugged
            if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
                shuffle(currentPlayer, state);
            }

            drawCard(currentPlayer, state);
            cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                drawntreasure++;
            else{
                temphand[z]=cardDrawn;
                state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
                z++;
            }
        }

        while(z-1>=0){
            state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
            z=z-1;
        }

        return 0;

    ===================
    Adventurer Parameters (Inputs): state, currentPlayer, handPos
    ===================

    ===================
    Adventurer Expectations (from Assignment 3):
    ===================
*       TEST 1 - draw cards until two treasure cards are drawn (+2 overall)
*       TEST 2 - player's treasure cards increases by 2
*       TEST 3 - not add any actions to turn (card is terminal)
*       TEST 4 - kingdom and victory card piles should not change
*       TEST 5 - gameState should not change for any other players



*/

// NOTE: This code was used with permission from Elizabeth Emerson, my teammate in CS 362.
//  The code for this random test was written exclusively by her, as I did not complete
//  the test for the previous assignment.


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"
#include <time.h>

//Takes in a Boolean; if true, prints success message, else prints failure message.
int assertTrue(int x) {

	if (x == 1) {
		printf("Success! All works as expected.\n");
		return 1;
	}

	printf("Fail! There is a bug in your code.\n");
	return 0;
}


//This function tests adventurer_card().
int check_adventurer(int p, struct gameState *G) {

	//Declaring variables to keep track of initial state of the game.
	int handCount = G->handCount[p];
	int deckSize = G->deckCount[p];
	int discardSize = G->discardCount[p];
	int actions = G->numActions;

	//Call Adventurer.
	adventurer_card(G, p);

	//Asserts that handCount is expected size.
	if(assertTrue(handCount+2 == G->handCount[p])){
		printf("You have added +1 to handCount.\n");
	}

	//Asserts that deck is expected size.
	if(assertTrue(deckSize > G->deckCount[p])) {
		printf("You have drawn cards.\n");
	}
}


//This is the main function.
int main() {

	//Declare relevant variables.
	int j, i, n, r, p, deckCount, discardCount, handCount, villageLoc, handPos;

	//Choose cards for the deck.
	int k[10] = {adventurer, gold, silver, copper, mine,
				remodel, smithy, village, feast, great_hall};

	//Declare gameState.
	struct gameState G;

	//Print to screen.
	printf ("Testing village_card.\n");
	printf ("RANDOM TESTS.\n");

	//Declare time for random function.
	time_t t;

   //Intializes random number generator.
   unsigned seed = (unsigned) time(&t);
   srand(seed);

	//Carries out test of Adventurer 2000 times.
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = rand() % 256;
		}

		//Get random player.
		p = rand() % 2;

		//Get random deck count.
		G.deckCount[p] = (rand() % (MAX_DECK -10)) +10;

		//Loop to fill the deck with cards.
		for (i = 0; i < G.deckCount[p]; i++) {

			//Choose a random card for k to put in the deck.
			G.deck[p][i] = k[rand() % 10];
		}

		//Get random hand count.
		G.handCount[p] = rand() % (MAX_HAND-(G.deckCount[p]-1))+1;

		//Loop to fill hand count with cards.
		for (i = 0; i < G.handCount[p]; i++) {

			//Choose a random card for k to put in the hand.
			G.hand[p][i] = k[rand() % 10];
		}

		//Get random discard count.
		G.discardCount[p] = MAX_DECK - G.deckCount[p] - G.handCount[p];

		//Loop to fill discard count with cards.
		for (i = 0; i < G.discardCount[p]; i++) {

			//Choose a random card for k to put in the discard pile.
			G.discard[p][i] = k[rand() % 10];
		}

		//Intialize other gameState variables.
		G.numActions = 1;
		G.outpostPlayed = 0;
		G.phase = 0;
		G.numBuys = 1;
		G.playedCardCount = 0;
		G.whoseTurn = p;

		//Print relevant information.
		printf ("\n\ntest #%d\ndeckCount: %d \ndiscardCount: %d\nhandCount: %d\n", n, G.deckCount[p],  G.discardCount[p], G.handCount[p]);

		//Call check_adventurer to check Adventurer card.
		check_adventurer(p, &G);
	}

	printf("Done Testing\n");

	exit(0);
 }
