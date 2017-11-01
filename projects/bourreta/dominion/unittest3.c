#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define NOISY_TEST 1

int main(){
    
    int supplyPosMax = treasure_map + 1;
    int r, s;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState G, pre;
    int testCase = 0;
    int failureCount = 0;
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(2, k, seed, &G); // initialize a new game, each player begins with 3 estates (3 VPs)
    memcpy(&pre, &G, sizeof(struct gameState));
    
#if (NOISY_TEST == 1)
    printf("\n**UNIT TEST 3: test of getCost() function**\n");
#endif
    
    for(s = 0; s < supplyPosMax + 1; s++){

#if (NOISY_TEST == 1)
        printf("\n**Test Case %d**\n", testCase);
        testCase++;
#endif
#if (NOISY_TEST == 1)
        printf("Testing card position #%d\n", s);
#endif
        r = getCost(s);
        
        if(s == curse || s == copper){
            if(r == 0){
#if (NOISY_TEST == 1)
                printf("\tPASS: Cost = %d, expected = 0\n", r);
            }
            else{
                printf("\tFAIL: Cost = %d, expected = 0\n", r);
                failureCount++;
            }
#endif
        }
        else if(s == estate || s == embargo){
#if (NOISY_TEST == 1)
            if(r == 2){
                printf("\tPASS: Cost = %d, expected = 2\n", r);
            }
            else{
                printf("\tFAIL: Cost = %d, expected = 2\n", r);
                failureCount++;
            }
#endif
        }
        else if(s == silver || s == village || s == ambassador || s == great_hall || s == steward){
#if (NOISY_TEST == 1)
            if(r == 3){
                printf("\tPASS: Cost = %d, expected = 3\n", r);
            }
            else{
                printf("\tFAIL: Cost = %d, expected = 3\n", r);
                failureCount++;
            }
#endif
        }
        else if(s == gardens || s == remodel || s == smithy || s == baron || s == cutpurse || s == salvager || s == sea_hag || s == treasure_map || s == feast){
#if (NOISY_TEST == 1)
            if(r == 4){
                printf("\tPASS: Cost = %d, expected = 4\n", r);
            }
            else{
                printf("\tFAIL: Cost = %d, expected = 4\n", r);
                failureCount++;
            }
#endif
        }
        else if(s == duchy || s == council_room || s == mine || s == minion || s == tribute || s == outpost){
#if (NOISY_TEST == 1)
            if(r == 5){
                printf("\tPASS: Cost = %d, expected = 5\n", r);
            }
            else{
                printf("\tFAIL: Cost = %d, expected = 5\n", r);
                failureCount++;
            }
#endif
        }
        else if(s == gold || s == adventurer){
#if (NOISY_TEST == 1)
            if(r == 6){
                printf("\tPASS: Cost = %d, expected = 5\n", r);
            }
            else{
                printf("\tFAIL: Cost = %d, expected = 5\n", r);
                failureCount++;
            }
#endif
        }
        else if(s == province){
#if (NOISY_TEST == 1)
            if(r == 8){
                printf("\tPASS: Cost = %d, expected = 5\n", r);
            }
            else{
                printf("\tFAIL: Cost = %d, expected = 5\n", r);
                failureCount++;
            }
#endif
        }
        else{
#if (NOISY_TEST == 1)
            if(r == -1 && s > 26){
                printf("\tPASS: function handled invalid card number: %d\n", s);
            }
            else{
                printf("\tFAIL: invalid card number: %d, not handled in getCost()\n", s);
                failureCount++;
            }
#endif
        }
    }
    
#if (NOISY_TEST == 1)
    printf("\n**Test Case %d**\n", testCase);
    testCase++;
#endif
#if (NOISY_TEST == 1)
    printf("Testing to ensure function has not altered gameState\n");
#endif
    
#if (NOISY_TEST == 1)
    if(memcmp(&G, &pre, sizeof(struct gameState)) == 0){
        printf("\tPASS: game state has not been altered\n");
    }
    else{
        printf("\tFAIL: game state has been changed\n");
        failureCount++;
    }
#endif
    
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
