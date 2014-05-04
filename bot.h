#include <vector>
#include <string>

#ifndef BOT_H
#define BOT_H

const int MAX_CARD_VALUE = 14;

class PresidentBot {

public:
	virtual std::string name () = 0;
	virtual void init(int players, int playerIndex, std::vector<int> cards) = 0;
	virtual std::vector<int> makeMove( bool newRound ) = 0;
	virtual void moveCallback(int player, std::vector<int>) = 0;

};

#endif