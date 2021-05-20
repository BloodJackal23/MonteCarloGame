#include <iostream>
#include "Card.h"
#include "CardDeck.h"


void WelcomeMessage()
{
    std::cout << "Welcome to the Monte Carlo card game.\n";
}

void ExplanationMessage()
{
    std::cout << "You are presented with 3 cards. One of them is a winner while the other 2 are not. You wil choose one card, then one of the other 2 will be removed from the deck." << std::endl
        << "You will then be offered a chance to change your selection to the other card. The answer will be displayed at the end of each round with your overall performance." << std::endl
        << "Choose wisely and Good Luck :)\n";
}

void DisplaySelectionMessage()
{
    std::cout << "Please, select a card (from 1 to 3)\n";
}

void InvalidSelectionMessage()
{
    std::cout << "Sorry, but this was an invalid selection. Please, try again.\n";
}

void ExitMessage()
{
    std::cout << "Play again? Y to play again, N to exit\n";
}

void RemovedCardMessage(int _index)
{
    std::cout << "Card #" << _index + 1 << " has been removed!\n" << "Would you like to switch? Y to switch, N to stay\n";
}

void DisplayResults(int _stayCount, int _switchCount, int _stayWins, int _switchWins)
{
    std::cout << "You have won " << _stayWins << " time/s out of " << _stayCount << " by staying with your current selection." << std::endl <<
        "You have won " << _switchWins << " time/s out of " << _switchCount << " by switching your current selection.\n";
}

bool SelectedYes()
{
    char input;
    do
    {
        std::cin >> input;
        if (input == 'y' || input == 'Y')
            return true;
        else if (input == 'n' || input == 'N')
            return false;
        else
            InvalidSelectionMessage();
    }     while (true);
}

int SelectCard(int _size)
{
    int selection;
    std::cin >> selection;

    while (std::cin.fail() || selection < 1 || selection > _size)
    {
        std::cin.clear(); // reset failbit
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        InvalidSelectionMessage();
        std::cin >> selection;
    }
    return selection - 1;
}

int GetRemainingCard(int _deckSize, int _current, int _removed)
{
    for (int i = 0; i < _deckSize; i++)
    {
        if (i != _current && i != _removed)
            return i;
    }
}

int SwitchCardSelection(int _current, int _remaining)
{
    if (SelectedYes())
        return _remaining;
    else
        return _current;
}

bool ExitGame()
{
    ExitMessage();
    if (SelectedYes())
    {
        system("cls");
        return false;
    }
    else
        return true;
}

int main()
{
    int stayWins = 0, switchWins = 0, stayCount = 0, switchCount = 0 , currentSelection, removedCard, remainingCard, newSelection;
    bool selectionSwitched = false;
    CardDeck deck;

    WelcomeMessage();
    ExplanationMessage();
    do
    {
        int winner = deck.GetRandomNumber(3);

        Card* cards = deck.BuildDeck();
        DisplaySelectionMessage();
        currentSelection = SelectCard(deck.DECK_SIZE);
        std::cout << "Card #" << currentSelection + 1 << " selected..." << std::endl;
        removedCard = deck.RemoveCardFromDeck(cards, currentSelection);
        RemovedCardMessage(removedCard);
        remainingCard = GetRemainingCard(deck.DECK_SIZE, currentSelection, removedCard);
        newSelection = SwitchCardSelection(currentSelection, remainingCard);
        if (newSelection != currentSelection)
        {
            selectionSwitched = true;
            currentSelection = newSelection;
            switchCount++;
        }
        else
        {
            selectionSwitched = false;
            stayCount++;
        }
            
        Card selectedCard = *(cards + currentSelection);
        if (selectedCard.IsWinner())
        {
            if (selectionSwitched)
                switchWins++;
            else
                stayWins++;
            std::cout << "You Win :)" << std::endl;
        }
        else
            std::cout << "You lose :(" << std::endl;
        DisplayResults(stayCount, switchCount, stayWins, switchWins);
    }     
    while (!ExitGame());
    system("pause>0");
}

