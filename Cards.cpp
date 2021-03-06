// Cards.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdarg.h"
#include <stdio.h>
#pragma warning(disable : 4996)
#include "stdlib.h"
#include "string.h"
#include "time.h"

typedef enum S {
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
}SUIT;
char suits[][10] = { "CLUBS","DIAMONDS","HEARTS","SPADES" };

typedef enum F {
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
}FACE;

char faces[][10] = { "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE" };

typedef struct
{
	SUIT suit;
	FACE face;
} card;

typedef struct
{
	card cards[5];
}hand;


hand dealHand(hand handsDealt[], int numHandsDealt);
char * printCard(card aCard); 
char * compareCards(card yourCard, card dealersCard);
bool fourAces(hand aHand);

void main()
{
	int i = 0;
	hand myHand, dealersHand;
	int seed = time(NULL);
	srand(seed);
	hand hands[10];

	myHand = dealHand(hands, 0);
	hands[0] = myHand;
	dealersHand = dealHand(hands, 1);

	while (i < 5) {
		printf("Card#%d: %s (you) vs. %s (dealer) . Winner: %s \n", i + 1, printCard(myHand.cards[i]), printCard(dealersHand.cards[i]), compareCards(myHand.cards[i], dealersHand.cards[i]));
		i++;
	}

	while (1)
	{
	
		myHand = dealHand(hands, 0);

		if (fourAces(myHand)) break;
		i++; 
	}
	
	printf("\n\n4 aces found after %d hands \n\n\n", i);

}

char * compareCards(card yourCard, card dealersCard)
{
	char * sptr;
	sptr = (char *)malloc(10 * sizeof(char));

	if (yourCard.face > dealersCard.face) {
		strcpy(sptr, "YOU");
	}
	else if (yourCard.face < dealersCard.face) {
		strcpy(sptr, "DEALER");
	}
	else if (yourCard.face == dealersCard.face) {
		strcpy(sptr, "DRAW");
	}

	return sptr;
}



hand dealHand(hand handsDealt[], int numHands) {


	int i;
	int n;
	int found = 1;
	hand newHand;
	int numCards = 0;

	SUIT newSuit;
	FACE newFace;
	for (i = 0; i < 5; i++) {
		while (found != 0) {

			newFace = TWO;
			newSuit = CLUBS;
			
			newFace = FACE(int(newFace) + (rand() % 13));
			newSuit = SUIT(int(newSuit) + (rand() % 4));

			if (numCards > 0 || numHands > 0) {

				for (n = 0; n < numCards; n++) {
					if (newHand.cards[n].face == newFace && newHand.cards[n].suit == newSuit) {
						found = 2;
					}
				}
				for (n = 0; n < numHands; n++) {
					if (handsDealt[n].cards->face == newFace && handsDealt[n].cards->suit == newSuit) {
						found = 2;
					}
					else {
						break;
					}
				}
				found -= 1;

			}
			numCards++;
			newHand.cards[i].suit = newSuit;
			newHand.cards[i].face = newFace;
			


		}
		found = 1;
	}

	return newHand;
}


char * printCard(card aCard)
{
	char * sptr;

	sptr = (char *)malloc(10 * sizeof(10));
	strcpy(sptr, faces[aCard.face]);
	strcat(sptr, " OF ");
	strcat(sptr, suits[aCard.suit]);
	return sptr;
}

bool fourAces(hand aHand)
{
	int i=0;
	int numAces = 0;
	bool fourAces = false;

	
	for (i = 0; i < 5; i++) {
		if (aHand.cards[i].face == ACE) {
			numAces++;
		}if (numAces == 4) {
			fourAces = true;
		}
	}

	return fourAces;

}