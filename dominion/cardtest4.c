#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
void assertTrue_salvager(struct gameState *CardTest);

int main() {
	struct gameState *CardTest;
	CardTest = newGame();
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest);
	printf("Test Start+++++++++++++++++++Card Test 4 ++++++++test card: salvgar \n");
	assertTrue_salvager(CardTest);
	printf("Test End+++++++++++++++++++++Card Test 4 ++++++++test card: salvgar \n");
	return 0;
}

void assertTrue_salvager(struct gameState *CardTest) {
	int player;
	player = CardTest->whoseTurn;
	CardTest->hand[player][0] = silver;
	CardTest->hand[player][1] = council_room;
	CardTest->hand[player][2] = copper;
	CardTest->hand[player][3] = copper;
	CardTest->hand[player][4] = salvager;
	CardTest->coins = 0;
	printf("Case:           whoseTurn = 0, handCount[0] = 5,  hand[0][4] = salvagr, hand[0][1]= concil_room\n");
	printf("Correct Result: played card is 1, player hand count is 3 (5-1-1), coins = 5 (0+5)\n");
	cardEffect(salvager, 1, 0, 0, CardTest, 4, 0);
	if (CardTest->playedCardCount == 1
		&& CardTest->playedCards[0] == salvager
		&& CardTest->handCount[player] == 3
		&& CardTest->coins == 5)
		printf("work \n");
	else
		printf("wrong\n");
}
