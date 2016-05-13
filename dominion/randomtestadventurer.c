#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define MAX_TEST 50
#define PLAYER 2
#define TRUE 1
#define FALSE 0

int main (int argc, char* argv[]) {
	int seed, hand_count, deck_count, discard_count, card_pos;
	int initial_treasure, current_treasure;
	int empty_deck;
	int i, j;
	int player;
	int card;
	time_t t;
	if (argc == 2) {
		printf ("Take input seed\n");
		seed = atoi(argv[1]);
	}
	else {
		printf ("Take fixed seed\n");
		seed = rand()%20 + 1;
	}
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	card_pos = 0;
	srand((unsigned) time(&t));
	struct gameState *ranTest;
	for (i = 0; i < MAX_TEST; i++) {
		initial_treasure = 0;
		current_treasure = 0;
		empty_deck = 0;	
		ranTest = newGame();
		initializeGame(PLAYER, Kingdom_Card, seed, ranTest);
		player = ranTest->whoseTurn;
		hand_count = rand()%20;
		ranTest->handCount[player] = hand_count;
		ranTest->hand[player][0] = adventurer;
		for (j = 1; j < hand_count; j++){
			card = rand()%27;
			if (card == copper || card == silver || card == gold) {
				initial_treasure++;
			}
			ranTest->hand[player][j] = card;
		}
		deck_count = rand()%30;
		printf ("deck_count %d\n",deck_count);
		if (deck_count == 0) {
			empty_deck = TRUE;
		}
		ranTest->deckCount[player] = deck_count;
		for (j = 0; j < (deck_count - 2); j++){
			card = rand() % 27;
			ranTest->deck[player][j] = card;
		}
		discard_count = rand()%10;
		ranTest->discardCount[player] = discard_count;
		ranTest->discard[player][0] = copper;
		ranTest->discard[player][1] = copper;
		for (j = 2; j < (discard_count -1); j++){
			card = rand() % 27;
			ranTest->discard[player][j] = card;
		}
		cardEffect(adventurer, 0, 0, 0, ranTest, card_pos, 0);
		for (j = 0; j< ranTest->handCount[player]; j++) {
			if (ranTest->hand[player][j] == copper || ranTest->hand[player][j] == silver || ranTest->hand[player][j] == gold) {
				current_treasure++;
			}
		}
		if (current_treasure == (initial_treasure + 2)) {
			printf("RDT-adventurer: Success---Get two treasure cards\n");
		}
		else {
			printf("RDT-adventurer: Fail------Cannot get two treasure cards\n");
		}
		if (empty_deck == 1) {
			printf("RDT-adventurer: The deck is initialized as emoty state\n");
		}
		if (ranTest->handCount[player] == (hand_count + 2 - 1)) {
			printf("RDT-adventurer: Success---Get right hand count\n");
		}
		else {
			printf("RDT-adventurer: Fail------Get wrong hand count\n");
		}
		if (ranTest->playedCardCount == 1) {
			printf("RDT-adventurer: Success---Get right played card count\n");
		}
		else {
			printf("RDT-adventurer: Fail------Get wrong played card count\n");
		}
		free(ranTest);
	}	
	return 0;
}