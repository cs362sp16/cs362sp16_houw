#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
/*This unit test aim to test the correctness of function drawCard ()
  Since the drawCard () called in the initializeGame(), the current player's hand count should be five
*/
void assertTrue_DrawCard(struct gameState *CardTest);

int main() {
	struct gameState *CardTest;
	CardTest = newGame();
	int Kingdom_Card[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(PlayerNum, Kingdom_Card, 1, CardTest);
	printf("Test Start------------------Unit Test 1 ---test drawCard() \n");
	assertTrue_DrawCard(CardTest);
	printf("Test End--------------------Unit Test 1 ---test drawCard() \n");
	return 0;
}

void assertTrue_DrawCard(struct gameState *CardTest) {
	if (numHandCards(CardTest) == 5)
		printf("FUNCTION - drawCard() - works\n");
	else
		printf("FUNCTION - drawCard() - wrong\n");
}
