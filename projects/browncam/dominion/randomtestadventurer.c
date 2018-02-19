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


int main(){
    printf("Skipping random test for Adventurer");
    
    return 0;
}