//
//  randomtestcard1.c
//
//
//  Created by Andrew Bourret on 10/31/17.
//
//
#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define NOISY_TEST 1

void printCardName(int card){
    switch(card){
        case curse:
            printf("curse");
            break;
        case estate:
            printf("estate");
            break;
        case duchy:
            printf("duchy");
            break;
        case province:
            printf("province");
            break;
        case copper:
            printf("copper");
            break;
        case silver:
            printf("silver");
            break;
        case gold:
            printf("gold");
            break;
        case adventurer:
            printf("adventurer");
            break;
        case council_room:
            printf("council room");
            break;
        case feast:
            printf("feast");
            break;
        case gardens:
            printf("gardens");
            break;
        case mine:
            printf("mine");
            break;
        case remodel:
            printf("remodel");
            break;
        case smithy:
            printf("smithy");
            break;
        case village:
            printf("village");
            break;
        case baron:
            printf("baron");
            break;
        case great_hall:
            printf("great hall");
            break;
        case minion:
            printf("minion");
            break;
        case steward:
            printf("steward");
            break;
        case tribute:
            printf("tribute");
            break;
        case ambassador:
            printf("ambassador");
            break;
        case cutpurse:
            printf("cut purse");
            break;
        case embargo:
            printf("embargo");
            break;
        case outpost:
            printf("outpost");
            break;
        case salvager:
            printf("salvager");
            break;
        case sea_hag:
            printf("sea hag");
            break;
        case treasure_map:
            printf("treasure map");
            break;
    }
}

void randomizeGameState(struct gameState* state){
    int i,j;
    int numPlayers = 2;
    int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int curseDifference;
    int estateDifference;
    int duchyDifference;
    int provinceDifference;
    int copperDifference;
    int silverDifference;
    int goldDifference;
    int kingdomCardDifferences[treasure_map + 1];
    int randCount;
    int validGameState = 0;
    
    while(!validGameState){
        
        validGameState = 1;
        
        memset(state, 0, sizeof(struct gameState));   // clear the game state
        
        if (numPlayers == 2)
        {
            state->supplyCount[curse] = (rand() % (11 - 1)) + 1;
            curseDifference = 10 - state->supplyCount[curse];
        }
        else if (numPlayers == 3)
        {
            state->supplyCount[curse] = (rand() % (21 - 1)) + 1;
            curseDifference = 20 - state->supplyCount[curse];
        }
        else
        {
            state->supplyCount[curse] = (rand() % (31 - 1)) + 1;
            curseDifference = 30 - state->supplyCount[curse];
        }
        
        if (numPlayers == 2)
        {
            state->supplyCount[estate] = (rand() % (9 - 1)) + 1;
            estateDifference = 8 - state->supplyCount[estate];
            state->supplyCount[duchy] = (rand() % (9 - 1)) + 1;
            duchyDifference = 8 - state->supplyCount[duchy];
            state->supplyCount[province] = (rand() % (9 - 1)) + 1;
            provinceDifference = 8 - state->supplyCount[province];
        }
        else
        {
            state->supplyCount[estate] = (rand() % (13 - 1)) + 1;
            estateDifference = 12 - state->supplyCount[estate];
            state->supplyCount[duchy] = (rand() % (13 - 1)) + 1;
            duchyDifference = 12 - state->supplyCount[duchy];
            state->supplyCount[province] = (rand() % (13 - 1)) + 1;
            provinceDifference = 12 - state->supplyCount[province];
        }
        
        state->supplyCount[copper] = (rand() % (61 - 1)) + 1; //60 - (7 * numPlayers);
        copperDifference = 60 - state->supplyCount[copper];
        state->supplyCount[silver] = (rand() % (41 - 1)) + 1;
        silverDifference = 40 - state->supplyCount[silver];
        state->supplyCount[gold] = (rand() % (31 - 1)) + 1;
        goldDifference = 30 - state->supplyCount[gold];
        
        for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
        {
            for (j = 0; j < 10; j++)           		//loop chosen cards
            {
                if (kingdomCards[j] == i)
                {
                    //check if card is a 'Victory' Kingdom card
                    if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
                    {
                        if (numPlayers == 2){
                            state->supplyCount[i] = (rand() % (9 - 1)) + 1;
                            kingdomCardDifferences[i] = 8 - state->supplyCount[i];
                        }
                        else{
                            state->supplyCount[i] = (rand() % (13 - 1)) + 1;
                            kingdomCardDifferences[i] = 12 - state->supplyCount[i];
                        }
                    }
                    else
                    {
                        state->supplyCount[i] = (rand() % (11 - 1)) + 1;
                        kingdomCardDifferences[i] = 10 - state->supplyCount[i];
                    }
                    break;
                }
                else    //card is not in the set choosen for the game
                {
                    state->supplyCount[i] = -1;
                    kingdomCardDifferences[i] = -1;
                }
            }
        }
        
        for(i = 0; i < numPlayers; i++){
            state->deckCount[i] = 0;
            state->handCount[i] = 0;
            state->discardCount[i] = 0;
            
            //put at least one copper in each player's hand
            state->deck[i][state->deckCount[i]] = copper;
            state->deckCount[i]++;
            
            if(state->supplyCount[copper] > 0){
                state->supplyCount[copper]--;
            }
            else{
                copperDifference--;
            }
        }
        
        //distribute each left over pile of cards into player hands
        while(curseDifference){
            for(i = 0; i < numPlayers; i++){
                if(curseDifference > 0){
                    state->deck[i][state->deckCount[i]] = curse;
                    state->deckCount[i]++;
                    curseDifference--;
                }
            }
        }
        
        while(estateDifference){
            for(i = 0; i < numPlayers; i++){
                if(estateDifference > 0){
                    state->deck[i][state->deckCount[i]] = estate;
                    state->deckCount[i]++;
                    estateDifference--;
                }
            }
        }
        
        while(duchyDifference){
            for(i = 0; i < numPlayers; i++){
                if(duchyDifference > 0){
                    state->deck[i][state->deckCount[i]] = duchy;
                    state->deckCount[i]++;
                    duchyDifference--;
                }
            }
        }
        
        while(provinceDifference){
            for(i = 0; i < numPlayers; i++){
                if(provinceDifference > 0){
                    state->deck[i][state->deckCount[i]] = province;
                    state->deckCount[i]++;
                    provinceDifference--;
                }
            }
        }
        
        while(copperDifference){
            for(i = 0; i < numPlayers; i++){
                if(copperDifference > 0){
                    state->deck[i][state->deckCount[i]] = copper;
                    state->deckCount[i]++;
                    copperDifference--;
                }
            }
        }
        
        while(silverDifference){
            for(i = 0; i < numPlayers; i++){
                if(silverDifference > 0){
                    state->deck[i][state->deckCount[i]] = silver;
                    state->deckCount[i]++;
                    silverDifference--;
                }
            }
        }
        
        while(goldDifference){
            for(i = 0; i < numPlayers; i++){
                if(goldDifference > 0){
                    state->deck[i][state->deckCount[i]] = gold;
                    state->deckCount[i]++;
                    goldDifference--;
                }
            }
        }
        
        for(i = adventurer; i <= treasure_map; i++){
            while(state->supplyCount[i] > 0){
                for(j = 0; j < numPlayers; j++){
                    if(state->supplyCount[i] > 0){
                        state->deck[j][state->deckCount[j]] = i;
                        state->deckCount[j]++;
                        state->supplyCount[i]--;
                    }
                }
            }
        }
        
        //shuffle player decks
        for (i = 0; i < numPlayers; i++)
        {
            if ( shuffle(i, state) < 0 )
            {
                validGameState = 0;
            }
        }
        
        
        //set embargo tokens to 0 for all supply piles
        for (i = 0; i <= treasure_map; i++)
        {
            state->embargoTokens[i] = 0;
        }
        
        //initialize random player's turn
        state->outpostPlayed = 0;
        state->phase = 0;
        state->numActions = (rand() % (3 - 1)) + 1;
        state->numBuys = (rand() % (3 - 1)) + 1;
        state->playedCardCount = 0;
        state->whoseTurn = rand() % numPlayers;
        
        randCount = (rand() % (11 - 4)) + 4;
        //Moved draw cards to here, only drawing at the start of a turn
        for (i = 0; i < randCount; i++){
            drawCard(state->whoseTurn, state);
        }
        
        //put random number of cards in played pile
        randCount = (rand() % (4 - 0)) + 0;
        for(i = 0; i < randCount; i++){
            state->playedCards[state->playedCardCount] = state->hand[state->whoseTurn][state->handCount[state->whoseTurn] - 1];
            state->hand[state->whoseTurn][state->handCount[state->whoseTurn]] = -1;
            state->handCount[state->whoseTurn]--;
            state->playedCardCount++;
        }
        
        //put random number of cards in discard pile from deck
        randCount = (rand() % (state->deckCount[state->whoseTurn] - 0)) + 0;
        for(i = 0; i < randCount; i++){
            state->discard[state->whoseTurn][state->discardCount[state->whoseTurn]] = state->deck[state->whoseTurn][state->deckCount[state->whoseTurn] - 1];
            state->deck[state->whoseTurn][state->deckCount[state->whoseTurn] - 1] = -1;
            state->deckCount[state->whoseTurn]--;
            state->discardCount[state->whoseTurn]++;
        }
        
        if(validGameState){
            validGameState = isGameOver(state);
        }
        
    }
    
}

int main(){
    int i,j, k, n = 10;
    int result;
    int failureCount = 0;
    int preCallTreasureCount, postCallTreasureCount, preAdventurerDiscard, postAdventurerDiscard, preAdventurerPlayed, postAdventurerPlayed;
    struct gameState G, pre;
    
    srand(time(NULL));
    
    
    /*
     printf("How many tests?\n");
     
     scanf("%d", &n);
    */
    
#if (NOISY_TEST == 1)
    printf("**TESTING ADVENTURER CARD**\n");
#endif
    
    for(j = 1; j <= n; j++){
        
        preCallTreasureCount = 0;
        postCallTreasureCount = 0;
        preAdventurerDiscard = 0;
        postAdventurerDiscard = 0;
        preAdventurerPlayed = 0;
        postAdventurerPlayed = 0;
        
        randomizeGameState(&G);
        G.hand[G.whoseTurn][G.handCount[G.whoseTurn]] = adventurer; //add adventurer to player 0 hand
        G.handCount[G.whoseTurn]++;
        memset(&pre, 0, sizeof(struct gameState));   // clear the game state
        
        for(i = 0; i < G.handCount[G.whoseTurn]; i++){         //count initial treasure cards
            if(G.hand[G.whoseTurn][i] == copper || G.hand[G.whoseTurn][i] == silver || G.hand[G.whoseTurn][i] == gold) {preCallTreasureCount++;}
        }
        
        for(i = 0; i < G.discardCount[G.whoseTurn]; i++){         //count initial adventurer
            if(G.discard[G.whoseTurn][i] == adventurer) {preAdventurerDiscard++;}
        }
        
        for(i = 0; i < G.playedCardCount; i++){         //count initial adventurer
            if(G.playedCards[i] == adventurer) {preAdventurerPlayed++;}
        }
        memcpy(&pre, &G, sizeof(struct gameState)); //copy gameState into pre
        
        result = cardEffect(adventurer, 0, 0, 0, &G, G.handCount[G.whoseTurn] - 1, NULL);
        
        for(i = 0; i < G.handCount[G.whoseTurn]; i++){         //count initial treasure cards
            if(G.hand[G.whoseTurn][i] == copper || G.hand[G.whoseTurn][i] == silver || G.hand[G.whoseTurn][i] == gold) {postCallTreasureCount++;}
        }
        
        for(i = 0; i < G.discardCount[G.whoseTurn]; i++){         //count initial adventurer
            if(G.discard[G.whoseTurn][i] == adventurer) {postAdventurerDiscard++;}
        }
        
        for(i = 0; i < G.playedCardCount; i++){         //count initial adventurer
            if(G.playedCards[i] == adventurer) {postAdventurerPlayed++;}
        }
        
#if (NOISY_TEST == 1)
        printf("\n**Test Case %d**\n", j);
#endif
        
#if (NOISY_TEST == 1)
        printf("\tRandomized gameState: player's turn: %d, player %d's handCount: %d, deckCount: %d, discardCount %d, numBuys: %d, numActions: %d, playedCardCount: %d\n", pre.whoseTurn, pre.whoseTurn, pre.handCount[pre.whoseTurn], pre.deckCount[pre.whoseTurn], pre.discardCount[pre.whoseTurn], pre.numBuys, pre.numActions, pre.playedCardCount);
        printf("\tCards in hand: ");
        for(k = 0; k < pre.handCount[pre.whoseTurn]; k++){
            printCardName(pre.hand[pre.whoseTurn][k]);
            if(k < pre.handCount[pre.whoseTurn] - 1){
                printf(", ");
            }
            else{
                printf(".\n");
            }
        }
#endif
        


        
#if (NOISY_TEST == 1)
        printf("\n\ta. Checking return result\n");
#endif
        if(result == 0){
#if (NOISY_TEST == 1)
            printf("\t\tPASS: return result: %d, expected: 0\n", result);
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("\t\tFAIL: return result: %d, expected: 0\n", result);
#endif
            failureCount++;
        }
        
#if (NOISY_TEST == 1)
        printf("\n\tb. Checking if player hand gained two treasures\n");
#endif
        if(postCallTreasureCount == preCallTreasureCount + 2){
#if (NOISY_TEST == 1)
            printf("\t\tPASS: player hand gained two treasures\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("\t\tFAIL: treasures(post-call): %d, treasures(pre-call): %d\n", postCallTreasureCount, preCallTreasureCount);
#endif
            failureCount++;
        }
        
#if (NOISY_TEST == 1)
        printf("\n\tc. Checking if adventurer card was removed from player hand (placed in discard/played pile)\n");
#endif
        if((G.discardCount[G.whoseTurn] > pre.discardCount[G.whoseTurn] || G.playedCardCount == pre.playedCardCount + 1) && (postAdventurerDiscard > preAdventurerDiscard || postAdventurerPlayed > postAdventurerDiscard)){
#if (NOISY_TEST == 1)
            printf("\t\tPASS: adventurer card removed from players hand\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("\t\tFAIL: adventurer cards in discard pile(post-call): %d, adventurer cards in played pile(post-call): %d\n", postAdventurerDiscard, postAdventurerPlayed);
            printf("\t\tadventurer cards in discard pile(pre-call): %d, adventurer cards in played pile(pre-call): %d\n", preAdventurerDiscard, preAdventurerPlayed);
            printf("\t\tDeck count(post-call): %d, deck count(pre-call): %d\n", G.deckCount[G.whoseTurn], pre.deckCount[pre.whoseTurn]);
            printf("\t\tDiscard count(post-call): %d, discard count(pre-call): %d\n", G.discardCount[G.whoseTurn], pre.discardCount[pre.whoseTurn]);
#endif
            failureCount++;
        }
        
#if (NOISY_TEST == 1)
        printf("\n\td. Checking if cards were removed from player deck\n");
#endif
        if((G.deckCount[G.whoseTurn] < pre.deckCount[pre.whoseTurn]) || ((G.deckCount[G.whoseTurn] > pre.deckCount[G.whoseTurn]) && (G.discardCount[G.whoseTurn] < pre.discardCount[pre.whoseTurn]))){
#if (NOISY_TEST == 1)
            printf("\t\tPASS: cards removed from player deck\n");
#endif
        }
        else{
#if (NOISY_TEST == 1)
            printf("\t\tFAIL: Deck count(post-call): %d, Deck count(pre-call): %d\n", G.deckCount[G.whoseTurn], pre.deckCount[G.whoseTurn]);
            printf("\t\tDeck count(post-call): %d, deck count(pre-call): %d\n", G.deckCount[G.whoseTurn], pre.deckCount[pre.whoseTurn]);
            printf("\t\tDiscard count(post-call): %d, discard count(pre-call): %d\n", G.discardCount[G.whoseTurn], pre.discardCount[pre.whoseTurn]);
#endif
            failureCount++;
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
