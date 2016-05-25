#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define TRUE 1
#define FALSE 0

void num2card(int num, char *card) {
	switch (num) {
	case 0 :
		strcpy(card, "curse");
		break;
	case 1:
		strcpy(card,  "estate");
		break;
	case 2:
		strcpy(card,  "duchy");
		break;
	case 3:
		strcpy(card,  "province");
		break;
	case 4:
		strcpy(card,  "copper");
		break;
	case 5:
		strcpy(card,  "silver");
		break;
	case 6:
		strcpy(card,  "gold");
		break;
	case 7:
		strcpy(card,  "adventurer");
		break;
	case 8:
		strcpy(card,  "council_room");
		break;
	case 9:
		strcpy(card,  "feast");
		break;
	case 10:
		strcpy(card,  "gardens");
		break;
	case 11:
		strcpy(card,  "mine");
		break;
	case 12:
		strcpy(card,  "remodel");
		break;
	case 13:
		strcpy(card,  "smithy");
		break;
	case 14:
		strcpy(card,  "village");
		break;
	case 15:
		strcpy(card,  "baron");
		break;
	case 16:
		strcpy(card,  "great_hall");
		break;
	case 17:
		strcpy(card,  "minion");
		break;
	case 18:
		strcpy(card,  "steward");
		break;
	case 19:
		strcpy(card,  "tribute");
		break;
	case 20:
		strcpy(card,  "ambassador");
		break;
	case 21:
		strcpy(card,  "cutpurse");
		break;
	case 22:
		strcpy(card,  "embargo");
		break;
	case 23:
		strcpy(card,  "outpost");
		break;
	case 24:
		strcpy(card,  "salvager");
		break; 
	case 25:
		strcpy(card,  "sea_hag");
		break; 
	case 26:
		strcpy(card,  "treasure_map");
		break;
	}
}

int check_duplicate(int card, int *holder) {
	int i;
	for (i = 0; i < 10; i++) {
		if (card == holder[i])
			return TRUE;
	}
	return FALSE;
}

void random_kingdom_card(int *holder) {
	int card;
	int i;
	for (i = 0; i < 10; i++) {
		do
		{
			card = rand() % 20 + 7;
		} while (check_duplicate (card, holder));
		holder[i] = card;
		//printf("kingdom %d\n", holder[i]);
	}
}

void GetRandomGame(int seed, struct gameState *new_game, int *kingdom_card) {
	int player_num;
	player_num = rand() % 2 + 2;
	random_kingdom_card(kingdom_card);
	initializeGame(player_num, kingdom_card, seed, new_game);
}

int choose_card(struct gameState *random_game) {
	int hand_count;
	int card_index;
	int temp_card;
	int action_card_flag;
	int i;
	action_card_flag = FALSE;
	hand_count = random_game->handCount[random_game->whoseTurn];
	for (i = 0; i < hand_count; i++) {
		temp_card = random_game->hand[random_game->whoseTurn][i];
		if (temp_card >= adventurer && temp_card <= treasure_map)
			action_card_flag = TRUE;
	}
	if (!action_card_flag || hand_count == 0)
		return -1;			//no action card to play

	hand_count = random_game->handCount[random_game->whoseTurn];
	do {
		card_index = rand() % hand_count;
	} while (random_game->hand[random_game->whoseTurn][card_index] < adventurer
		|| random_game->hand[random_game->whoseTurn][card_index] > treasure_map);
	return card_index;
}

void make_choice(int *choice, struct gameState *random_game, int card_index, int *kingdomcard) {
	int hand_count;
	int card;
	int index;
	int choc;
	hand_count = numHandCards(random_game);
	card = random_game->hand[random_game->whoseTurn][card_index];
	switch (card)
	{
	case adventurer :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case council_room :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case feast :
		choc = rand() % 3 - 1;
		if (choc) {
			do {
				index = rand() % 10;
			} while (getCost(kingdomcard[index]) > 5);
			choice[0] = kingdomcard[index];
		}
		else {
			if (choc == 0) {
				choice[0] = copper;
			}
			else {
				choice[0] = silver;
			}
		}
			choice[1] = -1;
			choice[2] = -1;
			break;
	case gardens :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case mine :
			choice[0] = rand() % hand_count;
			choice[1] = rand() % 27;
			choice[2] = -1;
			break;
	case remodel :
			choice[0] = rand() % hand_count;
			choice[1] = rand() % 27;
			choice[2] = -1;
			break;
	case smithy :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case village :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case baron :
			choice[0] = rand() % 2;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case great_hall :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case minion :
			if (rand() % 2) {
				choice[0] = 1;
				choice[1] = -1;
				choice[2] = -1;
			}
			else {
				choice[0] = -1;
				choice[1] = 1;
				choice[2] = -1;
			}
			break;
	case steward :
			choice[0] = rand() % 3 + 1;
			choice[1] = -1;
			choice[2] = -1;
			if (choice[0] == 3 && hand_count >= 3) {
				do {
					choice[1] = rand() % hand_count;
					choice[2] = rand() % hand_count;
				} while (choice[2] == choice[1]
					|| random_game->hand[random_game->whoseTurn][choice[1]] == steward
					|| random_game->hand[random_game->whoseTurn][choice[2]] == steward);
			}
			break;
	case tribute :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case ambassador :
			do {
				choice[0] = rand() % hand_count;
			} while (random_game->hand[random_game->whoseTurn][choice[0]] == ambassador);
			choice[1] = 1;
			choice[2] = -1;
			break;
	case cutpurse :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case embargo :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case outpost :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case salvager :
			do {
				choice[0] = rand() % hand_count;
			} while (random_game->hand[random_game->whoseTurn][choice[0]] == salvager);
			choice[1] = -1;
			choice[2] = -1;
			break;
	case sea_hag :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	case treasure_map :
			choice[0] = -1;
			choice[1] = -1;
			choice[2] = -1;
			break;
	default:
		choice[0] = -1;
		choice[1] = -1;
		choice[2] = -1;
		break;
	}
}

void action_phase(struct gameState *random_game, int *kingdom_card) {
	int card_index;
	int choice[3];
	int round_count;
	int hand_count;
	char card[12];
	round_count = random_game->numActions;
	hand_count = random_game->handCount[random_game->whoseTurn];
	if (round_count != 0 && hand_count != 0) {
		card_index = choose_card(random_game); // check hand count 
		//printf("choose card %d card index %d\n", random_game->hand[random_game->whoseTurn][card_index], card_index);
		if (card_index != -1) {
			make_choice(choice, random_game, card_index, kingdom_card);
			//printf("done choice \n");
			num2card(random_game->hand[random_game->whoseTurn][card_index], card);
			printf("\tPlaying card %s\n", card);
			playCard(card_index, choice[0], choice[1], choice[2], random_game);
			round_count = random_game->numActions;
			hand_count = random_game->handCount[random_game->whoseTurn];
			//printf("result %d \n", result);
			//printf("action num %d \n", round_count);
			//assert(round_count <= 2);
		}
	}
}

void random_buy(struct gameState *random_game) {
	int target_card;
	char card[12];
	do {
		target_card = rand() % 27;
	} while (getCost(target_card) > random_game->coins || random_game->supplyCount[target_card] == 0);
	buyCard(target_card, random_game);
	num2card(target_card, card);
	printf("\tBuying card %s \n", card);
}

void buy_phase(struct gameState *random_game) {
	updateCoins(random_game->whoseTurn, random_game, 0);
	while (random_game->coins >= 0 && random_game->numBuys > 0)
	{
		random_buy(random_game);
	}
}

int main(int argc, char *argv[]) {
	int random_seed;
	int random_kingdom[10];
	int i;
	time_t t;
	int player_max[4];
	struct gameState *random_game;
	srand((unsigned)time(&t));
	if (argc < 2)
	{
		printf("Usage: .\testdominion seed\n");
		return 1;
	}
	random_seed = atoi(argv[1]);
	for (i = 0; i < 10; i++) {
		random_game = newGame();
		GetRandomGame(random_seed, random_game, random_kingdom);
		while (!isGameOver(random_game)) {
			printf("Player NO.%d's turn\n", random_game->whoseTurn);
			action_phase(random_game, random_kingdom);
			printf("Player NO.%d's action done\n", random_game->whoseTurn);
			buy_phase(random_game);
			printf("Player NO.%d's buy done\n", random_game->whoseTurn);
			endTurn(random_game);
			printf("Player NO.%d's round done\n", random_game->whoseTurn);
		}
		printf("Game over.\n");
		getWinners(player_max, random_game);
		for (int i = 0; i < 4; i++) {
			if (player_max[i]) {
				printf("Player %d won!\n", i);
			}
		}
		free(random_game);
	}
	return 0;
}