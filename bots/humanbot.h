#ifndef HUMANBOT_H
#define HUMANBOT_H

#include "../bot.h"
#include <vector>
#include <string>

class HumanPresident : public PresidentBot {

	std::vector<int> cards;
	int playerIndex;

public:

	virtual std::string name ();
	
	virtual void init(int players, int playerIndex, std::vector<int> cards);

	virtual std::vector<int> makeMove( bool newRound );

	virtual void moveCallback(int player, std::vector<int>);
};

#endif