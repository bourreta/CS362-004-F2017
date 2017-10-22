#include "dominion.h"
#include "dominion_helpers.h"
#include "string.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){
    struct gameState G, pre;
    int i, j, r, result;
    int failureCount = 0;
    int smithyDiscard = 0;
    int smithyPlayed = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
#if (NOISY_TEST == 1)
    printf("**TESTING SMITHY CARD**\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(2, k, seed, &G); // initialize a new game

    G.hand[0][G.handCount[0]] = smithy; //add smithy to player 0 hand
    G.handCount[0]++;
    
    memcpy(&pre, &G, sizeof(struct gameState)); //copy gameState into pre
    
    result = cardEffect(smithy, 0, 0, 0, &G, G.handCount[0] - 1, NULL);
    
    for(i = 0; i < G.discardCount[0]; i++){         //count council_room in discard
        if(G.discard[0][i] == smithy) {smithyDiscard++;}
    }
    
    for(i = 0; i < G.playedCardCount; i++){         //count council_room in played cards
        if(G.playedCards[i] == smithy) {smithyPlayed++;}
    }
    
        //RETURN RESULT CHECK
#if (NOISY_TEST == 1)
        printf("\nChecking return result\n");
#endif
        if(result == 0){
#if (NOISY_TEST == 1)
            printf("PASS: return result: %d, expected: 0\n", result);
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("FAIL: return result: %d, expected: 0\n", result);
#endif
            failureCount++;
        }
        //HAND CARDS CHECK
#if (NOISY_TEST == 1)
        printf("\nChecking if player hand gained three cards\n");
#endif
        if(G.handCount[0] == pre.handCount[0] + 2){
#if (NOISY_TEST == 1)
            printf("PASS: Player hand gained three cards\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("FAIL: Hand count(post-call): %d, Hand count(pre-call): %d\n", G.handCount[0], pre.handCount[0]);
#endif
            failureCount++;
        }
        //DISCARD CHECK
#if (NOISY_TEST == 1)
        printf("\nChecking if smithy card was placed in discard/played pile\n");
#endif
        if((G.discardCount[0] > 0 || G.playedCards > 0) && (smithyDiscard || smithyPlayed)){
#if (NOISY_TEST == 1)
            printf("PASS: Smithy card was removed from player hand and placed in played/discard pile\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("FAIL: Smithy cards in discard: %d, council room cards in played card pile: %d ", smithyDiscard, smithyPlayed);
#endif
            failureCount++;
        }
        //DECK COUNT CHECK
#if (NOISY_TEST == 1)
        printf("\nChecking if the three drawn cards were removed from player deck\n");
#endif
        if(G.deckCount[0] == pre.deckCount[0] - 3){
#if (NOISY_TEST == 1)
            printf("PASS: Three cards removed from player deck\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("FAIL: Deck count(post-call): %d, Deck count(pre-call): %d\n", G.deckCount[0], pre.deckCount[0]);
#endif
            failureCount++;
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
if(failureCount){
#if (NOISY_TEST == 1)
        printf("\n**SUMMARY: FAILURES IN %d TESTS**\n", failureCount);
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("\n**SUMMARY: ALL TESTS PASS**\n");
#endif
    }
    return 0;
}
