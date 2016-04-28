#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
/*This unit test aim to test the correctness of function isGameOver ()
Determing whether a round of game is end or not is important.
*/
void assertTrue_isGameOver(struct gameState *CardTest, int choice);

int main() {
	int temp;
	struct gameState *CardTest;
	CardTest = newGame();
	int Kingdom_Card[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest);
	printf("Test Start------------------Unit Test 2 ---test isGameOver() \n");
	assertTrue_isGameOver(CardTest,	3);
	temp = CardTest->supplyCount[province];
	CardTest->supplyCount[province] = 0;
	assertTrue_isGameOver(CardTest, 1);
	CardTest->supplyCount[province] = temp;
	CardTest->supplyCount[0] = 0;
	CardTest->supplyCount[1] = 0;
	CardTest->supplyCount[2] = 0;
	assertTrue_isGameOver(CardTest, 2);
	printf("Test End---------------------Unit Test 2 ---test isGameOver() \n");
	return 0;
}

void assertTrue_isGameOver(struct gameState *CardTest, int choice) {
	if (choice == 1) {
		printf("test case: the game is over---Province is emmpty\n");
		if (isGameOver(CardTest) == 1)
			printf("FUNCTION - isGameOver() - works\n");
		else
			printf("FUNCTION - isGameOver() - wrong\n");
	}
	else if (choice == 2) {
		printf("test case: the game is over---Three supply pile are empty\n");
		if (isGameOver(CardTest) == 1)
			printf("FUNCTION - isGameOver() - works\n");
		else
			printf("FUNCTION - isGameOver() - wrong\n");
	}
	else {
		printf("test case: the game is not over\n");
		if (isGameOver(CardTest) == 0)
			printf("FUNCTION - isGameOver() - works\n");
		else
			printf("FUNCTION - isGameOver() - wrong\n");
	}
}
