#include "Problem54.h"
#include <fstream>
#include <algorithm>
//26 * 14 + 12 <- Just so I know if I break it

/*
TODO:
1)Encode the cards rank into a single value that can be compared

2)Try to reduce and/or eliminate if statements where possible

*/

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

bool Problem54::loadFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		return false;

	char round[30];
	for (int i = 0; i < rounds; i++)
	{
		file.getline(round, 30);
		for (int hand = 0; hand < 2; hand++)
		{
			Hand* cur = &hands[i * 2 + hand];
			int suit = round[hand * 15 + 1];
			for (int card = 0; card < 5; card++)
			{
				cur->cards[card] = cardValueToInt(round[hand * 15 + card * 2 + card]);
				cur->counts[cur->cards[card]]++;
				if (suit != round[hand * 15 + card * 2 + card + 1])
					cur->flush = false;
			}
		}
	}
	file.close();
	return true;
}


bool Problem54::getStraight(Hand hand)
{
	//Ace is a pain... I could wrap around but then what happens if
	//I get K,A,2,3,4
	int c = 0;
	int prev = hand.cards[0] + 1;
	if (hand.cards[0] == 13 && hand.cards[4] == 1)
	{
		c = 2;
		prev = hand.cards[1];
	}
	for (; c < 5; c++)
	{
		if (!(hand.cards[c] + 1 == prev))
			return false;
		prev = hand.cards[c];
	}
	return true;
}

std::vector<int> Problem54::getRank(Hand hand)
{
	//Vector containing the Hands rank and then the cards in the 
	//appropriate compare order
	std::vector<int> rank;
	//If all cards are the same suit and the lowest card is a Ten
	//then it must be a royal flush
	std::sort(hand.cards.begin(), hand.cards.end(), std::greater<int>());
	if (hand.flush && hand.cards[4] == 9)
	{
		rank.push_back(10);
		return rank;
	}

	bool straight = getStraight(hand);

	//If flush we can rule out cards with the same value
	if (straight)
	{
		if (hand.flush)
		{
			rank.push_back(9);
			//If the straight contains a low A the highest card is a 5
			hand.cards[0] == 13 && hand.cards[4] == 1 ?
				rank.push_back(4) : rank.push_back(hand.cards[0]);
		}
		rank.push_back(5);
		//If the straight contains a low A the highest card is a 5
		hand.cards[0] == 13 && hand.cards[4] == 1 ?
			rank.push_back(4) : rank.push_back(hand.cards[0]);
		return rank;
	}

	if (hand.flush)
	{
		rank.push_back(6);
		for (int j = 0; j < 5; j++)
			rank.push_back(hand.cards[j]);
		return rank;
	}

	//Check for duplicate card values (pairs, three of a kind, etc)
	for (int i = 13; i > 0; i--)
	{
		if (hand.counts[i] == 4)
		{
			rank.push_back(8);
			rank.push_back(i);
			rank.push_back(hand.cards[0] == i ? hand.cards[4] : hand.cards[0]);
			return rank;
		}
		
		if (hand.counts[i] == 3)
		{
			int threeOfAKind = i;
			for (i--; i > 0; i--)
			{
				if (hand.counts[i] == 2)
				{
					rank.push_back(7);
					rank.push_back(threeOfAKind);
					rank.push_back(i);
					return rank;
				}
			}
			rank.push_back(4);
			rank.push_back(threeOfAKind);
			if (hand.cards[1] != threeOfAKind)
			{
				rank.push_back(hand.cards[1]);
				rank.push_back(hand.cards[0]);
			}
			else if(hand.cards[3] != threeOfAKind)
			{
				rank.push_back(hand.cards[4]);
				rank.push_back(hand.cards[3]);
			}
			else
			{
				rank.push_back(hand.cards[4]);
				rank.push_back(hand.cards[0]);
			}
			return rank;
		}
		
		if (hand.counts[i] == 2)
		{
			int pair = i;
			for (i--; i > 0; i--)
			{
				if (hand.counts[i] == 3)
				{
					rank.push_back(7);
					rank.push_back(i);
					rank.push_back(pair);
					return rank;
				}
				if (hand.counts[i] == 2)
				{
					rank.push_back(3);
					rank.push_back(pair);
					rank.push_back(i);
					//We know i < pair and cards[0] is the smallest value
					if (hand.cards[0] != i)
						rank.push_back(hand.cards[0]);
					else
						hand.cards[2] == pair ? rank.push_back(hand.cards[4]) :
							rank.push_back(hand.cards[2]);
					return rank;
				}
			}
			rank.push_back(2);
			rank.push_back(pair);

			//Iterate through cards until pair is found then
			//skip it and the if statement in subsequent iterations
			for (int c = 0; c < 5; c++)
				if (hand.cards[c] != pair)
					rank.push_back(hand.cards[c]);
				else
					for (c += 2; c < 5; c++)
						rank.push_back(hand.cards[c]);

			return rank;
		}
	}

	rank.push_back(1);
	for (int c = 0; c < 5; c++)
		rank.push_back(hand.cards[c]);
	return rank;
}

bool Problem54::isPlayer1Winner(Hand playerHand, Hand opponentHand)
{
	std::vector<int> playerRank, opponentRank;
	playerRank = getRank(playerHand);
	opponentRank = getRank(opponentHand);
	
	for (int r = 0; r < playerRank.size(); r++)
		if (playerRank[r] > opponentRank[r])
			return true;
		else if (playerRank[r] < opponentRank[r])
			return false;

	return false;
}


std::string Problem54::solution()
{
	try
	{
		if (!loadFile("../resources/poker.txt"))
			return "Error: Unable to open file: ../resources/poker.txt";
	}
	catch (std::exception e)
	{
		return e.what();
	}


	int player1WinCount = 0;
	for (int r = 0; r < rounds; r++)
	{
		if (isPlayer1Winner(hands[r * 2], hands[r * 2 + 1]))
			player1WinCount++;
	}


	return std::to_string(player1WinCount);
}