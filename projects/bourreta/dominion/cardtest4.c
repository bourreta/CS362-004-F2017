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
    int villagePlayed = 0;
    int villageDiscard = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(2, k, seed, &G); // initialize a new game
    
    G.hand[0][G.handCount[0]] = village; //add village to player 0 hand
    G.handCount[0]++;

    memcpy(&pre, &G, sizeof(struct gameState)); //copy gameState into pre
    
    result = cardEffect(village, 0, 0, 0, &G, G.handCount[0] - 1, NULL);

    for(i = 0; i < G.discardCount[0]; i++){         //count council_room in discard
        if(G.discard[0][i] == village) {villageDiscard++;}
    }
    
    for(i = 0; i < G.playedCardCount; i++){         //count council_room in played cards
        if(G.playedCards[i] == village) {villagePlayed++;}
    }

#if (NOISY_TEST == 1)
    printf("**TESTING VILLAGE CARD**\n");
#endif
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
    printf("\nChecking if player hand gained one card\n");
#endif
    if(G.handCount[0] == pre.handCount[0]){
#if (NOISY_TEST == 1)
        printf("PASS: Player hand gained one card\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: Hand count(post-call): %d, Hand count(pre-call): %d\n", G.handCount[0], pre.handCount[0]);
#endif
        failureCount++;
    }
    //ACTIONS CHECK
#if (NOISY_TEST == 1)
    printf("\nChecking if player gained two actions\n");
#endif
    if(G.numActions == pre.numActions + 2){
#if (NOISY_TEST == 1)
        printf("PASS: Player gained two actions\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: Action count(post-call): %d, Action count(pre-call): %d\n", G.numActions, pre.numActions);
#endif
        failureCount++;
    }
    //DISCARD CHECK
#if (NOISY_TEST == 1)
    printf("\nChecking if village card was placed in discard/played pile\n");
#endif
    if((G.discardCount[0] > 0 || G.playedCards > 0) && (villageDiscard || villagePlayed)){
#if (NOISY_TEST == 1)
        printf("PASS: Village card was removed from player hand and placed in played/discard pile\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: Village cards in discard: %d, council room cards in played card pile: %d ", villageDiscard, villagePlayed);
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
