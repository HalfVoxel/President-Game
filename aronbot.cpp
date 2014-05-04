#include <iostream>
#include <vector>
#include <sstream>
#include "aronbot.h"

using namespace std;

string AronPresident::name () {
	return "Aron";
}

void AronPresident::init(int players, int playerIndex, vector<int> _cards) {
	cout << "I was initialized with cards: " << endl;
	cards = _cards;
	this->playerIndex = playerIndex;
	sort(cards.begin(),cards.end());
	for ( int c : cards ) cout << c << " ";
	
	cout << endl;
}

vector<int> AronPresident::makeMove( bool newRound ) {
	
}

bool isWild ( int v ) {
	return v == 2 || v == 3;
}

int findValue ( const vector<int>& move ) {
	int v = -1;
	for ( int a : move ) if (!isPrime(v))
}

void AronPresident::moveCallback(int player, vector<int> move ) {
	if ( playerIndex == player ) {
		for ( int c : move ) cards.erase ( find ( cards.begin(), cards.end(), c ) );
	} else {
		
	}
}