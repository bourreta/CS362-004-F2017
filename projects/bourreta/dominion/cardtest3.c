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
    int councilDiscard = 0;
    int councilPlayed = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
#if (NOISY_TEST == 1)
    printf("**TESTING COUNCIL ROOM CARD**\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(2, k, seed, &G); // initialize a new game

    
    G.hand[0][G.handCount[0]] = council_room; //add council room to player 0 hand
    G.handCount[0]++;
    
    memcpy(&pre, &G, sizeof(struct gameState)); //copy gameState into pre
    
    result = cardEffect(council_room, 0, 0, 0, &G, G.handCount[0] - 1, NULL);
    
    for(i = 0; i < G.discardCount[0]; i++){         //count council_room in discard
        if(G.discard[0][i] == council_room) {councilDiscard++;}
    }
    
    for(i = 0; i < G.playedCardCount; i++){         //count council_room in played cards
        if(G.playedCards[i] == council_room) {councilPlayed++;}
    }
    
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
#if (NOISY_TEST == 1)
    printf("\nChecking if player drew 4 cards\n");
#endif
    if(G.handCount[0] == pre.handCount[0] + 3){ //+3 because council_room should have been removed from hand
#if (NOISY_TEST == 1)
        printf("PASS: 4 cards added to player hand\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: Hand count(post-call): %d, Hand count(pre-call): %d\n", G.handCount[0], pre.handCount[0]);
#endif
        failureCount++;
    }
#if (NOISY_TEST == 1)
    printf("\nChecking if player gained one buy\n");
#endif
    if(G.numBuys == pre.numBuys + 1){
#if (NOISY_TEST == 1)
        printf("PASS: player gained one buy\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: number of buys(post-call): %d, number of buys(pre-call): %d\n", G.numBuys, pre.numBuys);
#endif
        failureCount++;
    }
#if (NOISY_TEST == 1)
    printf("\nChecking other player drew one card\n");
#endif
    if(G.handCount[1] == pre.handCount[1] + 1){
#if (NOISY_TEST == 1)
        printf("PASS: Other player drew a card\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: Other player hand count(pre-call): %d, Other player hand count(post-call): %d\n", pre.handCount[1], G.handCount[1]);
#endif
        failureCount++;
    }
    
#if (NOISY_TEST == 1)
    printf("\nChecking if council room card was placed in discard/played pile\n");
#endif
    if((G.discardCount[0] > 0 || G.playedCards > 0) && (councilDiscard || councilPlayed)){
#if (NOISY_TEST == 1)
        printf("PASS: Council room card was removed from player hand and placed in played/discard pile\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: Council room cards in discard: %d, council room cards in played card pile: %d ", councilDiscard, councilPlayed);
#endif
        failureCount++;
    }
    
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
