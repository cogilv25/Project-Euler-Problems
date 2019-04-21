#include "Problem54.h"
#include <fstream>
#include <algorithm>
//376 <- Just so I know if I break it


int Problem54::cardValueToInt(char value)
{
	switch (value)
	{
	case '2': return 1;
	case '3': return 2;
	case '4': return 3;
	case '5': return 4;
	case '6': return 5;
	case '7': return 6;
	case '8': return 7;
	case '9': return 8;
	case 'T': return 9;
	case 'J': return 10;
	case 'Q': return 11;
	case 'K': return 12;
	case 'A': return 13;
	//The challenge guarantees no incorrect values but
	//visual studio doesn't know that...
	default: throw std::exception("Error: Unknown card value");
	}
}

std::vector<int> Problem54::getHandRank(std::vector<int> hand, int * count, bool flush)
{
	//Vector containing the Hands rank and then the cards in the 
	//appropriate compare order
	std::vector<int> rank;
	//If all cards are the same suit and the lowest card is a Ten
	//then it must be a royal flush
	std::sort(hand.begin(), hand.end(), std::greater<int>());
	if (flush && hand[4] == 9)
	{
		rank.push_back(10);
		return rank;
	}

	bool straight=true;
	int prev = hand[0] + 1;
	int sc = 0;

	//Ace is a pain... I could wrap around but then what happens if
	// I get K,A,2,3,4
	if (hand[0] == 13 && hand[4] == 1)
	{ 
		sc = 2; 
		prev = hand[1]; 
	}


	for (; sc < 5; sc++)
	{
		if (!(hand[sc] + 1 == prev))
			straight = false;
		prev = hand[sc];
	}
	//If Flush we can rule out cards with the same value
	if (flush)
	{
		if (straight)
		{
			rank.push_back(9);
			if (hand[0] == 13 && hand[4] == 1)
				rank.push_back(4);
			else
				rank.push_back(hand[0]);
		}
		else
		{
			rank.push_back(6);
			for (int j = 0; j < 5; j++)
				rank.push_back(hand[j]);
		}
		return rank;
	}
	else
	{
		if (straight)
		{
			rank.push_back(5);
			if (hand[0] == 13 && hand[4] == 1)
				rank.push_back(4);
			else
				rank.push_back(hand[0]);
		}

		for (int i = 13; i > 0; i--)
		{
			if (count[i] == 4)
			{
				rank.push_back(8);
				rank.push_back(i);
				rank.push_back(hand[0] == i ? hand[4] : hand[0]);
				return rank;
			}
			else if (count[i] == 3)
			{
				int threeOfAKind = i;
				i--;
				for (; i > 0; i--)
				{
					if (count[i] == 2)
					{
						rank.push_back(7);
						rank.push_back(threeOfAKind);
						rank.push_back(i);
						return rank;
					}
				}
				rank.push_back(4);
				rank.push_back(threeOfAKind);
				for (int j = 0; j < 5; j++)
					if (hand[j] != threeOfAKind)
						rank.push_back(hand[j]);
				return rank;
			}
			else if (count[i] == 2)
			{
				int pair = i;
				i--;
				for (; i > 0; i--)
				{
					if (count[i] == 3)
					{
						rank.push_back(7);
						rank.push_back(i);
						rank.push_back(pair);
						return rank;
					}
					if (count[i] == 2)
					{
						rank.push_back(3);
						rank.push_back(pair);
						rank.push_back(i);
						for (int j = 0; j < 5; j++)
							if (hand[j] != pair && hand[j] != i)
								rank.push_back(hand[j]);
						return rank;
					}
				}
				rank.push_back(2);
				rank.push_back(pair);
				for (int j = 0; j < 5; j++)
					if (hand[j] != pair)
						rank.push_back(hand[j]);
				return rank;
			}
		}
	}

	rank.push_back(1);
	for (int c = 0; c < 5; c++)
		rank.push_back(hand[c]);
	return rank;
}

bool Problem54::player1Wins(char* round)
{
	std::vector<int> handRanks[2];

	for (int player = 0; player < 2; player++)
	{
		std::vector<int> hand(5);
		int cardValueCount[14] { 0 };
		bool flush = true;
		int suit = round[player * 15 + 1];
		for (int card = 0; card < 5; card++)
		{
			hand[card] = cardValueToInt(round[player * 15 + card*2 + card]);
			cardValueCount[hand[card]]++;
			if (round[player * 15 + card * 2 + card + 1] != suit)
				flush = false;
		}
		handRanks[player] = getHandRank(hand, cardValueCount, flush);
	}

	for (int i = 0; i < handRanks[0].size(); i++)
		if (handRanks[0][i] > handRanks[1][i])
			return true;
		else if (handRanks[0][i] < handRanks[1][i])
			return false;


	return false;
}

std::string Problem54::solution()
{
	std::ifstream file("../resources/poker.txt");
	if (!file.is_open())
		return "Error: Unable to open file: ../resources/poker.txt";

	int count = 0;
	char round[30];
	try {
		for (int i = 0; i < 1000; i++)
		{
			file.getline(round, 30);
			if (player1Wins(round))
				count++;
		}
	}
	catch (std::exception e)
	{
		return e.what();
	}

	file.close();
	return std::to_string(count);
}