#pragma once
#include <iostream>
class Card
{
private:
	bool isWinner = false;
public:
	int cardIndex = 0;
	void SetAsWinner(bool _value);
	bool IsWinner();
};

