#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_TEST 50
#define PLAYER 2
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[]) {
	int seed, hand_count, deck_count, discard_count, card_pos;
	int i, j;
	int player;
	int card;
	time_t t;
	if (argc == 2) {
		printf("Take input seed\n");
		seed = atoi(argv[1]);
	}
	else {
		printf("Take fixed seed\n");
		seed = rand() % 20 + 1;
	}
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	card_pos = 0;
	srand((unsigned)time(&t));
	struct gameState *ranTest;
	for (i = 0; i < MAX_TEST; i++) {
		ranTest = newGame();
		initializeGame(PLAYER, Kingdom_Card, seed, ranTest);
		player = ranTest->whoseTurn;
		hand_count = rand() % 20 + 2;
		ranTest->handCount[player] = hand_count;
		ranTest->hand[player][card_pos] = smithy;
		for (j = 1; j < hand_count; j++) {
			card = rand() % 27;
			ranTest->hand[player][j] = card;
		}
		deck_count = rand() % 30 + 3;
		ranTest->deckCount[player] = deck_count;
		for (j = 0; j < deck_count; j++) {
			card = rand() % 27;
			ranTest->deck[player][j] = card;
		}
		discard_count = rand() % 10;
		ranTest->discardCount[player] = discard_count;
		for (j = 0; j < discard_count; j++) {
			card = rand() % 27;
			ranTest->discard[player][j] = card;
		}
		cardEffect(smithy, 0, 0, 0, ranTest, card_pos, 0);
		if (ranTest->handCount[player] == (hand_count + 3 - 1))
			printf("RDT-smithy: Success---hand count correct\n");
		else
			printf("RDT-smithy: Fail------hand count incorrect\n");
		if (ranTest->deckCount[player] == (deck_count - 3))
			printf("RDT-smithy: Success---Deck count correct\n");
		else
			printf("RDT-smithy: Fail------Deck count incorrect\n");
		if (ranTest->discardCount[player] == discard_count)
			printf("RDT-smithy: Success---discard count correct\n");
		else
			printf("RDT-smithy: Fail------discard count incorrect\n");
		if (ranTest->playedCardCount == 1)
			printf("RDT-smithy: Success---Played card count correct\n");
		else
			printf("RDT-smithy: Fail------Played card count incorrect\n");

		free(ranTest);
	}
	return 0;
}