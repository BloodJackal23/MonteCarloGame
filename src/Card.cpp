#include "Card.h"

void Card::SetAsWinner(bool _value)
{
	isWinner = _value;
}

bool Card::IsWinner()
{
	return isWinner;
}
