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
	int choice;
	int sub_choice_1;
	int sub_choice_2;
	int initial_coins;
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
		choice = rand() % 3 + 1;
		ranTest = newGame();
		initializeGame(PLAYER, Kingdom_Card, seed, ranTest);
		player = ranTest->whoseTurn;
		hand_count = rand() % 20 + 3;
		ranTest->handCount[player] = hand_count;
		ranTest->hand[player][0] = steward;
		for (j = 1; j < hand_count; j++) {
			card = rand() % 27;
			ranTest->hand[player][j] = card;
		}
		if (choice == 3)
			do{
				sub_choice_1 = rand() % hand_count + 1;
				sub_choice_2 = rand() % hand_count + 1;
			} while (sub_choice_1 == sub_choice_2);
		deck_count = rand() % 30 + 2;
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
		ranTest->coins = rand() % 10;
		initial_coins = ranTest->coins;
		cardEffect(steward, choice, sub_choice_1, sub_choice_2, ranTest, card_pos, 0);
		printf("RDT-steward: Choice %d\n", choice);
		if (choice == 1) {
			if (ranTest->handCount[player] == (hand_count + 2 - 1))
				printf("RDT-steward: Success---Get two more cards\n");
			else
				printf("RDT-steward: Fail------Cannot get two more cards\n");
			if (ranTest->deckCount[player] == (deck_count - 2))
				printf("RDT-steward: Success---Deck count correct\n");
			else
				printf("RDT-steward: Fail------Deck count incorrect\n");
		}
		else if (choice == 2) {
			if (ranTest->coins == (2 + initial_coins))
				printf("RDT-steward: Success---Get two more coins\n");
			else
				printf("RDT-steward: Fail------Cannot get two more coins\n");
			if (ranTest->handCount[player] == (hand_count - 1))
				printf("RDT-steward: Success---hand count correct\n");
			else
				printf("RDT-steward: Fail------hand count incorrect\n");
			if (ranTest->deckCount[player] == deck_count)
				printf("RDT-steward: Success---Deck count correct\n");
			else
				printf("RDT-steward: Fail------Deck count incorrect\n");
		}
		else {
			if (ranTest->handCount[player] == (hand_count - 2 - 1))
				printf("RDT-steward: Success---hand count correct\n");
			else
				printf("RDT-steward: Fail------hand count incorrect\n");
			if (ranTest->deckCount[player] == deck_count)
				printf("RDT-steward: Success---Deck count correct\n");
			else
				printf("RDT-steward: Fail------Deck count incorrect\n");
		}
		if (ranTest->playedCardCount == 1) {
			printf("RDT-adventurer: Success---Get right played card count\n");
		}
		else {
			printf("RDT-adventurer: Fail------Get wrong played card count\n");
		}
		if (ranTest->discardCount[player] == discard_count)
			printf("RDT-steward: Success---discard count correct\n");
		else
			printf("RDT-steward: Fail------discard count incorrect\n");
		free(ranTest);
	}
}