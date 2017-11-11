#include "dominion.h"
#include "dominion_helpers.h"
#include "string.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){
    int i, j, r;
    int failureCount = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    int numPlayer = 3;
    int testScores[3] = {0};
    int result = 0;
    struct gameState G, pre;
    
#if (NOISY_TEST == 1)
    printf("\n**UNIT TEST 1: test of scoreFor() function**\n");
#endif
    
#if (NOISY_TEST == 1)
    printf("\nInitializing gameState with %d players\n", numPlayer);
#endif
    
    for(i = 0; i < numPlayer; i++){
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game, each player begins with 3 estates (3 VPs)
        memcpy(&pre, &G, sizeof(struct gameState));

#if (NOISY_TEST == 1)
        printf("\nTest Case %d\n", i + 1);
#endif
        if(i == 0){
#if (NOISY_TEST == 1)
            printf("Testing count of Victory Points for cards in player HAND\n");
            printf("\tMoving all player %d's cards to hand and counting initial estate victory points\n", i);
#endif
            for(j = G.deckCount[i]; j > 0; j--){ //transfer all player 0 cards from deck to hand
                G.hand[i][G.handCount[i]] = G.deck[i][G.deckCount[i] - 1];
                G.deck[i][G.deckCount[i] - 1] = -1;
                G.handCount[i]++;
                G.deckCount[i]--;
            }
            testScores[i] = 0;
            for(j = 0; j < G.handCount[i]; j++){

                if(G.hand[i][j] == estate) {testScores[i] +=  1;}
            }
#if (NOISY_TEST == 1)
            printf("\tPlayer %d score: %d\n", i, testScores[i]);
            printf("\tAdding victory point cards to player %d hand: 1x curse (-1 VP), 3x estate (1 VP), 2x duchy (3 VP)\n", i);
#endif
            gainCard(curse, &G, 2, i); //add curse to player 0's hand pile, score -1 VPs
            for(j = 0; j < 3; j++){
                gainCard(estate, &G, 2, i); //add three estates to player 0's hand pile, score +3 VPs
            }
            
            for(j = 0; j < 2; j++){
                gainCard(duchy, &G, 2, i); //add two duchy's to player 0's hand pile, +3 * 2 = 6 VPs
            }
            testScores[i] = 0;
            for(j = 0; j < G.handCount[i]; j++){
                if(G.hand[i][j] == estate) {testScores[i] +=  1;}
                if(G.hand[i][j] == duchy) {testScores[i] +=  3;}
                if(G.hand[i][j] == curse) {testScores[i] -=  1;}
            }
#if (NOISY_TEST == 1)
            printf("\tPlayer %d score: %d\n", i, testScores[i]);
#endif
        }
        else if(i == 1){
            testScores[i] = 0;
            for(j = 0; j < G.deckCount[i]; j++){
                if(G.deck[i][j] == estate) {testScores[i] +=  1;}
            }
#if (NOISY_TEST == 1)
            printf("Testing count of Victory Points for cards in player DECK\n");
            printf("\tMoving all cards to player's deck and counting player %d's initial estate victory points\n", i);
            printf("\tPlayer %d score: %d\n", i, testScores[i]);
            printf("\tAdding victory point cards to player %d deck: 3x duchy (3 VP), 2x province (6 VP), 1x great hall (1 VP)\n", i);
#endif
            for(j = 0; j < 3; j++){
                gainCard(duchy, &G, 1, i); //add three duchy to player 1's deck pile, score +3 x 3 VPs
            }
            for(j = 0; j < 2; j++){
                gainCard(province, &G, 1, i); //add two provinces to player's deck, score + 2 x 6VPs
            }
            gainCard(great_hall, &G, 1, i); //add one great hall to player 1's deck pile, score +1 VP
            testScores[i] = 0;
            for(j = 0; j < G.deckCount[i]; j++){
                if(G.deck[i][j] == estate) {testScores[i] += 1;}
                if(G.deck[i][j] == duchy) {testScores[i] += 3;}
                if(G.deck[i][j] == province) {testScores[i] += 6;}
                if(G.deck[i][j] == great_hall) {testScores[i] += 1;}
            }
            
        }
        else if(i == 2){
#if (NOISY_TEST == 1)
            printf("Testing count of Victory Points for cards in player DISCARD\n");
            printf("\tMoving all player %d's cards to discard and counting initial estate victory points\n", i);
#endif
            for(j = G.deckCount[i]; j > 0; j--){ //transfer all player 0 cards from deck to hand
                G.discard[i][G.discardCount[i]] = G.deck[i][G.deckCount[i] - 1];
                G.deck[i][G.deckCount[i] - 1] = -1;
                G.discardCount[i]++;
                G.deckCount[i]--;
            }
            testScores[i] = 0;
            for(j = 0; j < G.discardCount[i]; j++){
                if(G.discard[i][j] == estate) {testScores[i] +=  1;}
            }
            
            gainCard(duchy, &G, 0, i); //add 1 duchy to player 2's discard pile, score +3 x 1 VPs
            gainCard(province, &G, 0, i); //add two provinces to player's deck, score +1 x 6 VPs
            for(j = 0; j < 29; j++){
                gainCard(copper, &G, 0, i);
            }
            gainCard(gardens, &G, 0, i); //add one great hall to player 1's deck pile, score +1 VP
#if (NOISY_TEST == 1)
            printf("\tPlayer %d score: %d\n", i, testScores[i]);
            printf("\tAdding victory point cards to player %d discard: 1x duchy (3 VP), 1x province (6 VP), 1x garden (1 VP per 10 cards in deck), 30x copper)\n", i);
#endif
            testScores[i] = 0;
            for(j = 0; j < G.discardCount[i]; j++){
                if(G.discard[i][j] == estate) {testScores[i] +=  1;}
                if(G.discard[i][j] == duchy) {testScores[i] += 3;}
                if(G.discard[i][j] == province) {testScores[i] += 6;}
                if(G.discard[i][j] == gardens) {testScores[i] += ((G.deckCount[i] + G.discardCount[i] + G.handCount[i]) / 10);}
            }
        }

#if (NOISY_TEST == 1)
        printf("\tChecking player %d score with scoreFor()\n", i);
#endif
        memcpy(&pre, &G, sizeof(struct gameState));
        result = scoreFor(i, &G);
        if(result == testScores[i]){
#if (NOISY_TEST == 1)
            printf("\tPASS: Player %d results: %d, expected: %d\n", i, result, testScores[i]);
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("\tFAIL: Player %d results: %d, expected: %d\n", i, result, testScores[i]);
#endif
            failureCount++;
            //assert(result == testScores[i]);
        }
#if (NOISY_TEST == 1)
        printf("\tComparing game state from before and after scoreFor() call\n");
#endif
        if(memcmp(&pre, &G, sizeof(struct gameState)) == 0){
#if (NOISY_TEST == 1)
            printf("\tPASS: No modifications made to game state by scoreFor()\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            failureCount++;
            printf("\tFAIL: scoreFor() made modifications to game state\n");
#endif
            //assert(memcmp(&pre, &G, sizeof(struct gameState)) == 0); //check that scoreFor has not modified the game state
        }
        /*
         printf("G.handCount[%d]: %d\n", 0, G.handCount[0]);
         printf("G.deckCount[%d]: %d\n", 0, G.deckCount[0]);
         printf("G.playedCardCount: %d\n", G.playedCardCount);
         printf("G.discardCount[%d]: %d\n", 0, G.discardCount[0]);
         for(j = 0; j < G.handCount[0]; j++){
         printf("Player %d Hand: Card in Slot #%d: %d\n", 0, j, G.hand[0][j]);
         }
         for(j = 0; j < G.deckCount[0]; j++){
         printf("Player %d Deck: Card in Slot #%d: %d\n", 0, j, G.deck[0][j]);
         }
         for(j = 0; j < G.playedCardCount; j++){
         printf("Player %d Played Cards: Card in Slot #%d: %d\n", 0, j, G.playedCards[j]);
         }
         for(j = 0; j < G.discardCount[0]; j++){
         printf("Player %d Discard: Card in Slot #%d: %d\n", 0, j, G.discard[0][j]);
         }*/
    }
#if (NOISY_TEST == 1)
    if(failureCount){
        printf("\n**SUMMARY: FAILURES IN %d TESTS**\n", failureCount);
    }
    else{
        printf("\n**SUMMARY: ALL TESTS PASS**\n");
    }
#endif    
    return 0;
}
