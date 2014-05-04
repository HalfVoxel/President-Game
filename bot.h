#include <vector>
#include <string>

#ifndef BOT_H
#define BOT_H

const int MAX_CARD_VALUE = 14;

class PresidentBot {

public:

	bool isWild ( int c ) {
		return c == 2 || c == 3;
	}

	int findValue ( const std::vector<int>& move ) {
		for ( int a : move ) if (!isWild(a)) return a;
		return -1;
	}

	virtual std::string name () = 0;
	virtual void init(int players, int playerIndex, std::vector<int> cards) = 0;
	virtual std::vector<int> makeMove( bool newRound ) = 0;
	virtual void moveCallback(int player, std::vector<int>) = 0;

};

#endif