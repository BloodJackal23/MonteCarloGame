#include "CardDeck.h"

int CardDeck::GetRandomNumber(int _n)
{
	return (1.0 * _n * std::rand()) / (1.0 + RAND_MAX);
}

int CardDeck::RemoveCardFromDeck(Card* _deck, int _currentSelection)
{
	int rand;
	Card randCard;
	do
	{
		rand = GetRandomNumber(DECK_SIZE);
		randCard = *(_deck + rand);
		//Activate the following line if you want to see which card the program is currently trying to remove. Useful for debugging
		//std::cout << "Removing card #" << rand + 1 << "..." << std::endl;;
	} 	
	while (randCard.IsWinner() || randCard.cardIndex == _currentSelection);
	return randCard.cardIndex;
}

Card* CardDeck::BuildDeck()
{
	static Card tempCards[DECK_SIZE];
	int winningCard = GetRandomNumber(DECK_SIZE);
	for (int i = 0; i < DECK_SIZE; i++)
	{
		tempCards[i].cardIndex = i;
		if (i == winningCard)
			tempCards[i].SetAsWinner(true);
		else
			tempCards[i].SetAsWinner(false);
		//Activate the following line if you want to see the results before making a selection. Useful for debugging
		//std::cout << "Card #" << tempCards[i].cardIndex + 1 << " is a winner = " << tempCards[i].IsWinner() << std::endl;
	}
	return tempCards;
}
