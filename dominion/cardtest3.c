#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
void assertTrue_steward(struct gameState *CardTest, int choice);

int main() {
	struct gameState *CardTest;
	struct gameState *CardTest_1;
	struct gameState *CardTest_2;
	CardTest = newGame();
	CardTest_1 = newGame();
	CardTest_2 = newGame();
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest);
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest_1);
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest_2);
	printf("Test Start+++++++++++++++++++Card Test 3 ++++++++test card \n");
	assertTrue_steward(CardTest, 1);
	assertTrue_steward(CardTest_1, 2);
	assertTrue_steward(CardTest_2, 3);
	printf("Test End+++++++++++++++++++++Card Test 3 ++++++++test card \n");
	return 0;
}

void assertTrue_steward(struct gameState *CardTest, int choice) {
	int player;
	player = CardTest->whoseTurn;
	CardTest->hand[player][0] = silver;
	CardTest->hand[player][1] = copper;
	CardTest->hand[player][2] = copper;
	CardTest->hand[player][3] = copper;
	CardTest->hand[player][4] = steward;
	if (choice == 1){
		printf("Case:           whoseTurn = 0, handCount[0] = 5,  hand[0][4] = steward, add 2 cards to hand\n");
		printf("Correct Result: played card is 1, player hand count is 6 (5-1+2)\n");
		cardEffect(steward, choice, 0, 0, CardTest, 4, 0);
		if (CardTest->playedCardCount == 1
			&& CardTest->playedCards[0] == steward
			&& CardTest->handCount[player] == 6)
			printf("work \n");
		else
			printf("wrong\n");
	}
	else if (choice == 2){
		CardTest->coins = 0;
		printf("Case:           whoseTurn = 0, handCount[0] = 5,  hand[0][4] = steward, get two coins\n");
		printf("Correct Result: played card is 1, player hand count is 4 (5-1), coins = 2\n");
		cardEffect(steward, choice, 0, 0, CardTest, 4, 0);
		if (CardTest->playedCardCount == 1
			&& CardTest->playedCards[0] == steward
			&& CardTest->handCount[player] == 4
			&& CardTest->coins == 2)
			printf("work \n");
		else
			printf("wrong\n");
	}
	else {
		printf("Case:           whoseTurn = 0, handCount[0] = 5,  hand[0][4] = steward, trash two cards\n");
		printf("trash card index 1, 2\n");
		printf("Correct Result: played card is 1, player hand count is 2 (5-1-2)\n");
		cardEffect(steward, choice, 1, 2, CardTest, 4, 0);
		if (CardTest->playedCardCount == 1
			&& CardTest->playedCards[0] == steward
			&& CardTest->handCount[player] == 2)
			printf("work \n");
		else
			printf("wrong\n");
	}
}
