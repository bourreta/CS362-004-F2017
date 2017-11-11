#include "dominion.h"
#include "dominion_helpers.h"
#include "string.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){
    struct gameState G, pre;
    int i, r, result;
    //int j;
    int adventurerDiscard = 0;
    int adventurerPlayed = 0;
    int failureCount = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    int preCallTreasureCount = 0;
    int postCallTreasureCount = 0;
    
    
#if (NOISY_TEST == 1)
    printf("**TESTING ADVENTURER CARD**\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(2, k, seed, &G); // initialize a new game

    G.hand[0][G.handCount[0]] = adventurer; //add adventurer to player 0 hand
    G.handCount[0]++;
    
    for(i = 0; i < G.handCount[0]; i++){         //count initial treasure cards
        if(G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold) {preCallTreasureCount++;}
    }
    
    memcpy(&pre, &G, sizeof(struct gameState)); //copy gameState into pre
    
    result = cardEffect(adventurer, 0, 0, 0, &G, G.handCount[0] - 1, NULL); // call adventurer
    
    for(i = 0; i < G.handCount[0]; i++){         //count initial treasure cards
        if(G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold) {postCallTreasureCount++;}
    }
    
    for(i = 0; i < G.discardCount[0]; i++){         //count adventurer in discard
        if(G.discard[0][i] == adventurer) {adventurerDiscard++;}
    }
    
    for(i = 0; i < G.playedCardCount; i++){         //count adventurer in played
        if(G.playedCards[i] == adventurer) {adventurerPlayed++;}
    }
    
    /*assert(result == 0);
    assert(postCallTreasureCount == preCallTreasureCount + 2);
    assert(G.handCount[0] == pre.handCount[0] + 2);
    assert(G.discardCount[0] > pre.discardCount[0] || G.playedCardCount == pre.playedCardCount + 1);
    assert(G.deckCount[0] < pre.deckCount[0]);*/

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
    printf("\nChecking if player hand gained two treasures\n");
#endif
    if(postCallTreasureCount == preCallTreasureCount + 2){
#if (NOISY_TEST == 1)
        printf("PASS: player hand gained two treasures\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: treasures(post-call): %d, treasures(pre-call): %d\n", postCallTreasureCount, preCallTreasureCount);
#endif
        failureCount++;
    }
    
#if (NOISY_TEST == 1)
    printf("\nChecking if adventurer card was removed from player hand (placed in discard/played pile)\n");
#endif
    if((G.discardCount[0] > pre.discardCount[0] || G.playedCardCount == pre.playedCardCount + 1) && (adventurerDiscard > 0 || adventurerPlayed > 0)){
#if (NOISY_TEST == 1)
        printf("PASS: adventurer card removed from players hand\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("FAIL: adventurer cards in discard pile(post-call): %d, adventurer cards in played pile(post-call): %d\n", adventurerDiscard, adventurerPlayed);
#endif
        failureCount++;
    }
    
#if (NOISY_TEST == 1)
       printf("\nChecking if cards were removed from player deck\n");
#endif
       if(G.deckCount[0] < pre.deckCount[0]){
#if (NOISY_TEST == 1)
        printf("PASS: cards removed from player deck\n");
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
