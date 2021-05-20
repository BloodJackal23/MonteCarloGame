#pragma once
#include <iostream>
#include "Card.h"

class CardDeck
{	
public:
	static const int DECK_SIZE = 3;
	int GetRandomNumber(int _n), RemoveCardFromDeck(Card* _deck, int _currentSelection);
	Card* BuildDeck();
};

