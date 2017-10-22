#include "dominion.h"
#include "dominion_helpers.h"
#include "string.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main(){
    int i, j, r;
    int seed = 1000;
    int failureCount = 0;
    int numPlayer = 2;
    struct gameState G, pre;
    int result;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    int testCard = 0; // use valid value < 17
    int flagMax = 2;
    int testCase = 1;
    
#if (NOISY_TEST == 1)
    printf("\n**UNIT TEST 2: test of gainCard() function**\n");
#endif
    
    for(i = 0; i < numPlayer; i++){
        

        for(j = 0; j <= flagMax; j++){
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
            memcpy(&pre, &G, sizeof(struct gameState));

            
#if (NOISY_TEST == 1)
            printf("\n**Test case %d**\n", testCase);
#endif
            testCase++;
            //TEST ADDING CARD TO DISCARD PILE
            if(j == 0){
                printf("Test adding card to DISCARD with toFlag: %d, player: %d, card supplyPos: %d\n", j, i, testCard);

                result = gainCard(testCard, &G, j, i);
                
#if (NOISY_TEST == 1)
                printf("\tChecking return result\n");
#endif
                if(result == 0){
#if (NOISY_TEST == 1)
                    printf("\tPASS: return result: %d, expected: 0\n", result);
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: return result: %d, expected: 0\n", result);
#endif
                    failureCount++;
                }
                
#if (NOISY_TEST == 1)
                printf("\tChecking if card was added to discard pile\n");
#endif
                if(G.discardCount[i] == (pre.discardCount[i] + 1)){
#if (NOISY_TEST == 1)
                    printf("\tPASS: card added to discard\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Discard count(post-call): %d, Discard count(pre-call): %d\n", G.discardCount[i], pre.discardCount[i]);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if card on top of discard was the test card\n");
#endif
                if(G.discard[i][G.discardCount[i] - 1] == testCard){
#if (NOISY_TEST == 1)
                    printf("\tPASS: card on discard pile was test card\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Card on top of discard pile (post-call): %d, Test card: %d\n", G.discard[i][G.discardCount[i] - 1], testCard);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if test card supply was decremented\n");
#endif
                if(G.supplyCount[testCard] + 1 == pre.supplyCount[testCard] ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Supply decremented by 1 card\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Test card supply count(post-call): %d, Test card supply count(pre-call): %d\n", G.supplyCount[testCard], pre.supplyCount[testCard]);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if deck was unaffected by call to gainCard()\n");
#endif
                if( (G.deck[i][G.deckCount[i]] == pre.deck[i][pre.deckCount[i]]) && (G.deckCount[i] == pre.deckCount[i]) ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Deck unaffected by call to gainCard()\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Deck count(post-call): %d, Deck count(pre-call): %d\n", G.deckCount[i], pre.deckCount[i] );
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if hand was unaffected by call to gainCard()\n");
#endif
                if( (G.hand[i][G.handCount[i]] == pre.hand[i][G.handCount[i]]) && (G.handCount[i] == pre.handCount[i]) ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Hand unaffected by call to gainCard()\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Hand count(post-call): %d,  count(pre-call): %d\n", G.handCount[i], pre.handCount[i] );
#endif
                    failureCount++;
                }

                
            }
            //TEST ADDING CARD TO PLAYER DECK
            else if(j == 1){
                printf("Test adding card to DECK with toFlag: %d, player: %d, card supplyPos: %d\n", j, i, testCard);
                result = gainCard(testCard, &G, j, i);
#if (NOISY_TEST == 1)
                printf("\tChecking return result\n");
#endif
                if(result == 0){
#if (NOISY_TEST == 1)
                    printf("\tPASS: return result: %d, expected: 0\n", result);
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: return result: %d, expected: 0\n", result);
#endif
                    failureCount++;
                }
                
#if (NOISY_TEST == 1)
                printf("\tChecking if card was added to deck\n");
#endif
                if(G.deckCount[i] == (pre.deckCount[i] + 1)){
#if (NOISY_TEST == 1)
                    printf("\tPASS: card added to deck\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Deck count(post-call): %d, Deck count(pre-call): %d\n", G.deckCount[i], pre.deckCount[i]);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if card on top of deck was the test card\n");
#endif
                if(G.deck[i][G.deckCount[i] - 1] == testCard){
#if (NOISY_TEST == 1)
                    printf("\tPASS: card on deck pile was test card\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Card on top of deck(post-call): %d, Test card: %d\n", G.deck[i][G.deckCount[i] - 1], testCard);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if test card supply was decremented\n");
#endif
                if(G.supplyCount[testCard] + 1 == pre.supplyCount[testCard] ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Supply decremented by 1 card\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Test card supply count(post-call): %d, Test card supply count(pre-call): %d\n", G.supplyCount[testCard], pre.supplyCount[testCard]);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if discard was unaffected by call to gainCard()\n");
#endif
                if( (G.discard[i][G.discardCount[i]] == pre.discard[i][pre.discardCount[i]]) && (G.discardCount[i] == pre.discardCount[i]) ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Discard unaffected by call to gainCard()\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Discard count(post-call): %d, Discard count(pre-call): %d\n", G.discardCount[i], pre.discardCount[i] );
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if hand was unaffected by call to gainCard()\n");
#endif
                if( (G.hand[i][G.handCount[i]] == pre.hand[i][G.handCount[i]]) && (G.handCount[i] == pre.handCount[i]) ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Hand unaffected by call to gainCard()\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Hand count(post-call): %d, Hand count(pre-call): %d\n", G.handCount[i], pre.handCount[i] );
#endif
                    failureCount++;
                }

                
            }
            //TEST ADDING CARD TO PLAYER HAND
            else if(j == 2){
                
                printf("Test adding card to HAND with toFlag: %d, player: %d, card supplyPos: %d\n", j, i, testCard);
                result = gainCard(testCard, &G, j, i);
                
#if (NOISY_TEST == 1)
                printf("\tChecking return result\n");
#endif
                if(result == 0){
#if (NOISY_TEST == 1)
                    printf("\tPASS: return result: %d, expected: 0\n", result);
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: return result: %d, expected: 0\n", result);
#endif
                    failureCount++;
                }
                
#if (NOISY_TEST == 1)
                printf("\tChecking if card was added to hand\n");
#endif
                if( G.handCount[i] == (pre.handCount[i] + 1 )){
#if (NOISY_TEST == 1)
                    printf("\tPASS: card added to hand\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Hand count(post-call): %d, Hand count(pre-call): %d\n", G.handCount[i], pre.handCount[i]);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if card on top of hand was the test card\n");
#endif
                if(G.hand[i][G.handCount[i] - 1] == testCard){
#if (NOISY_TEST == 1)
                    printf("\tPASS: card on deck pile was test card\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Card on top of hand(post-call): %d, Test card: %d\n", G.hand[i][G.deckCount[i] - 1], testCard);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if test card supply was decremented\n");
#endif
                if(G.supplyCount[testCard] + 1 == pre.supplyCount[testCard] ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Supply decremented by 1 card\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Test card supply count(post-call): %d, Test card supply count(pre-call): %d\n", G.supplyCount[testCard], pre.supplyCount[testCard]);
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if discard was unaffected by call to gainCard()\n");
#endif
                if( (G.discard[i][G.discardCount[i]] == pre.discard[i][pre.discardCount[i]]) && (G.discardCount[i] == pre.discardCount[i]) ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Discard unaffected by call to gainCard()\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Discard count(post-call): %d, Discard count(pre-call): %d\n", G.discardCount[i], pre.discardCount[i] );
#endif
                    failureCount++;
                }
#if (NOISY_TEST == 1)
                printf("\tChecking if deck was unaffected by call to gainCard()\n");
#endif
                if( (G.deck[i][G.handCount[i]] == pre.deck[i][G.handCount[i]]) && (G.deckCount[i] == pre.deckCount[i]) ){
#if (NOISY_TEST == 1)
                    printf("\tPASS: Deck unaffected by call to gainCard()\n");
#endif
                }
                else{
#if (NOISY_TEST == 1)
                    printf("\tFAIL: Deck count(post-call): %d, Deck count(pre-call): %d\n", G.deckCount[i], pre.deckCount[i] );
#endif
                    failureCount++;
                }
            }
        }
    }

    //TEST GAINING CARD FROM EMPTY SUPPLY
    for(j = 0; j <= flagMax; j++){
        for(i = 0; i < numPlayer; i++){
#if (NOISY_TEST == 1)
            printf("\n**Test case %d**\n", testCase);
#endif
            testCase++;
            if(j == 0){
            printf("Test adding card to DISCARD with empty supplyCount for player: %d, using toFlag: %d**\n", i, j);
            }
            else if(j == 1){
#if (NOISY_TEST == 1)
            printf("Test adding card to card DECK with empty supplyCount for player: %d, using toFlag: %d**\n", i, j);
#endif
            }
            else{
            printf("Test adding card HAND with empty supplyCount for player: %d, using toFlag: %d**\n",  i, j);
            }
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
            
            G.supplyCount[testCard] = 0;
            
            memcpy(&pre, &G, sizeof(struct gameState));
            
            result = gainCard(testCard, &G, j, i);
            
            if(result == -1 && memcmp(&G, &pre, sizeof(struct gameState)) == 0){
#if (NOISY_TEST == 1)
                printf("\tPASS: supplyCount is empty for card %d, no card added to discard, hand, or deck\n", testCard);
#endif
            }
            else{
#if (NOISY_TEST == 1)
                printf("\tFAIL: supplyCount not empty using testCard: %d, toFlag: %d, player: %d | result == %d, expected: -1\n", testCard, j, i, result);
#endif
                failureCount++;
            }
            assert(result == -1);
            assert(memcmp(&G, &pre, sizeof(struct gameState)) == 0);
        }
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
