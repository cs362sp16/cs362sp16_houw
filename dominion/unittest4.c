#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
/*This unit test aim to test the correctness of function updateCoins()
*/
void assertTrue_updateCoins(struct gameState *CardTest);

int main() {
	struct gameState *CardTest;
	CardTest = newGame();
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest);
	printf("Test Start------------------Unit Test 4 ---test drawCard() \n");
	assertTrue_updateCoins(CardTest);
	printf("Test End--------------------Unit Test 4 ---test drawCard() \n");
	return 0;
}

void assertTrue_updateCoins(struct gameState *CardTest) {
	int player, bouns;
	player = CardTest->whoseTurn;
	bouns = 1;
	CardTest->hand[player][0] = copper;
	CardTest->hand[player][1] = copper;
	CardTest->hand[player][2] = silver;
	CardTest->hand[player][3] = silver;
	CardTest->hand[player][4] = gold;
	updateCoins(player, CardTest, bouns);
	printf("Expect value 10, Get Value %d", CardTest->coins);
	if (CardTest->coins == 2 + 4 + 3 + 1)
		printf("  work\n");
	else
		printf("  wrong\n");

}
