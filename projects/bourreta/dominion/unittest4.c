#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define NOISY_TEST 1

int main(){
    int r, s;
    int i = adventurer;
    int j = treasure_map;
    int l = smithy;
    int emptyPiles = 0;
    int numPlayer = 2;
    int result;
    int victoryQuantity;
    int failureCount = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int maxSupplyPos = treasure_map + 1;
    struct gameState G;
    int testCase = 1;
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    
    if(numPlayer == 2){
        victoryQuantity = 8;
    }
    else if(numPlayer > 2){
        victoryQuantity = 12;
    }

    //CHECK NEW GAME STATE
#if (NOISY_TEST == 1)
    printf("\nUNIT TEST 4: test of isGameOver() function**\n");
#endif
    for(s = 0; s < maxSupplyPos; s++){
        if(G.supplyCount[s] == 0){
            emptyPiles++;
        }
    }
#if (NOISY_TEST == 1)
    printf("\n**Test case %d\n", testCase);
    testCase++;
    printf("\tTesting function with newly initialized game\n");
#endif
    result = isGameOver(&G);

    if(result == 0 && emptyPiles == 0 && G.supplyCount[province] > 0){
        #if (NOISY_TEST == 1)
        printf("\tPASS: Game not over, still %d provinces and no empty piles\n", G.supplyCount[province]);
        #endif
    }
    else{
        #if (NOISY_TEST == 1)
        printf("\tFAIL: Return value: %d, expected: 0\n\tNumber of empty piles = %d\n\tNumber of provinces in supply: %d\n", result, emptyPiles, G.supplyCount[province]);
        #endif
        failureCount++;
    }
    //CHECK EMPTY PROVINCE PILE
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.supplyCount[province] = 0;
#if (NOISY_TEST == 1)
    printf("\n**Test case %d\n", testCase);
    testCase++;
    printf("Testing function with empty province pile\n");
#endif
    result = isGameOver(&G);

    if(result == 1 && G.supplyCount[province] == 0){
#if (NOISY_TEST == 1)
        printf("\tPASS: Game over. Return value: 1, Province pile empty\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("\tFAIL: Return value: %d, expected: 1\n\tNumber of cards in province pile = %d, expected = 0\n", result, G.supplyCount[province]);
#endif
        failureCount++;
    }


//CHECK ONE EMPTY PILE
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    //only run test if none of the cards are a province

#if (NOISY_TEST == 1)
    printf("\n**Test case %d\n", testCase);
    testCase++;
    printf("Testing function with ONE empty pile for non-province card position: %d\n", i);
#endif
    G.supplyCount[i] = 0;
    
    emptyPiles = 0;
    for(s = 0; s < maxSupplyPos; s++){
        if(G.supplyCount[s] == 0){
            emptyPiles++;
        }
    }

    result = isGameOver(&G);
    if(result == 0 && G.supplyCount[i] == 0 && emptyPiles == 1){
#if (NOISY_TEST == 1)
        printf("\tPASS: Game not over with ONE empty pile for non-province card\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("\tFAIL: Return value: %d, expected 0\n\tSupply count of card %d: %d, expected: 0\n\t Empty piles: %d, expected 1\n", result, i, G.supplyCount[i], emptyPiles);
#endif
        failureCount++;
    }


    

    //CHECK TWO EMPTY PILES
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    //only run test if none of the cards are a province

#if (NOISY_TEST == 1)
    printf("\n**Test case %d\n", testCase);
    testCase++;
    printf("Testing function with TWO empty piles for non-province cards positions: %d and %d\n", i, j);
#endif
    G.supplyCount[i] = 0;
    G.supplyCount[j] = 0;
    
    emptyPiles = 0;
    for(s = 0; s < maxSupplyPos; s++){
        if(G.supplyCount[s] == 0){
            emptyPiles++;
        }
    }
    
    result = isGameOver(&G);
    if(result == 0 && G.supplyCount[i] == 0 && G.supplyCount[j] == 0 && emptyPiles == 2){
#if (NOISY_TEST == 1)
        printf("\tPASS: Game not over with TWO empty non-province card supply piles\n");
#endif
    }
    else{
#if (NOISY_TEST == 1)
        printf("\tFAIL: Return value: %d, expected 0\n\tSupply count of card %d: %d, expected: 0\n\tSupply count of card %d: %d, expected: 0\n\t Empty piles: %d, expected 2\n", result, i, G.supplyCount[i], j, G.supplyCount[j], emptyPiles);
#endif
        failureCount++;
    }
        

    //CHECK THREE EMPTY PILES
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    //only run test if none of the cards are a province

#if (NOISY_TEST == 1)
        printf("\n**Test case %d\n", testCase);
        testCase++;
        printf("Testing function with THREE empty piles for non-province cards positions: %d, %d, and %d\n", i, j, l);
#endif
        G.supplyCount[i] = 0;
        G.supplyCount[j] = 0;
        G.supplyCount[l] = 0;
        emptyPiles = 0;
        for(s = 0; s < maxSupplyPos; s++){
            if(G.supplyCount[s] == 0){
                emptyPiles++;
            }
        }
        
        result = isGameOver(&G);
        if(result == 1 && G.supplyCount[i] == 0 && G.supplyCount[j] == 0 && G.supplyCount[l] == 0 && emptyPiles == 3){
#if (NOISY_TEST == 1)
            printf("\tPASS: Game is over with THREE empty non-province card piles\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("\tFAIL: Return value: %d, expected 1\n\tSupply count of card %d: %d, expected: 0\n\tSupply count of card %d: %d, expected: 0\n\tSupply count of card %d: %d, expected: 0\n\tEmpty piles: %d, expected 3\n", result, i, G.supplyCount[i], j, G.supplyCount[j], l, G.supplyCount[l],emptyPiles);
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
