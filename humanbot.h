#ifndef HUMANBOT_H
#define HUMANBOT_H

#include "bot.h"
#include <vector>

using namespace std;

class HumanPresident : public PresidentBot {

	vector<int> cards;
	int playerIndex;

public:

	virtual string name ();
	
	virtual void init(int players, int playerIndex, vector<int> cards);

	virtual vector<int> makeMove( bool newRound );

	virtual void moveCallback(int player, vector<int>);
};

#endif