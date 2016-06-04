#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define PlayerNum 2
/*This unit test aim to test the correctness of function getCost()
get cost for each type of cards. Different card has different value
*/
void assertTrue_getCost();

int main() {
	printf("Test Start------------------Unit Test 3 ---test getCost() \n");
	assertTrue_getCost();
	printf("Test End--------------------Unit Test 3 ---test getCost() \n");
	return 0;
}

void assertTrue_getCost() {
	int i, work, wrong;
	int cost[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	work = 0;
	wrong = 0;
	for (i = 0; i < 27; i++) {	 
		printf("Expected Value %d, getCost() return %d", cost[i], getCost(i));
		if (getCost(i) == cost[i]) {
			printf("  Work\n");
			work++;
		}
		else {
			printf("  Wrong\n");
			wrong++;
		}
	}
	printf("work %d wrong %d\n", work, wrong);
}
