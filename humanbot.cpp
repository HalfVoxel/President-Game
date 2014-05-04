#include<iostream>
#include<vector>
#include<sstream>
#include "humanbot.h"

using namespace std;

string HumanPresident::name () {
	return "HumanBot";
}

void HumanPresident::init(int players, int playerIndex, vector<int> _cards) {
	cout << "I was initialized with cards: " << endl;
	cards = _cards;
	this->playerIndex = playerIndex;
	sort(cards.begin(),cards.end());
	for ( int c : cards ) cout << c << " ";
	
	cout << endl;
}

vector<int> HumanPresident::makeMove( bool newRound ) {
	while (true) {
		cout << "My turn, I have these cards right now: ";
		for ( int c : cards ) cout << c << " ";
		cout << endl;

		cout << "Enter the cards: ";
		string s;
		getline(cin,s);
		istringstream ss (s);

		auto tmpCards = cards;
		vector<int> move;
		int tmp;
		while ( ss >> tmp ) {
			move.push_back(tmp);

			auto v = find (tmpCards.begin(), tmpCards.end(), tmp);
			if ( v != tmpCards.end() ) {
				tmpCards.erase (v);
			} else {
				cout << "We don't have a " << tmp << ". Try again. " << endl;
				goto end;
			}
		}
		return move;
		end:;
	}
}

void HumanPresident::moveCallback(int player, vector<int> move ) {
	if ( playerIndex == player ) {
		for ( int c : move ) cards.erase ( find ( cards.begin(), cards.end(), c ) );
	} else {
		cout << "Ok, then I know what " << player << " did" << endl;
	}
}