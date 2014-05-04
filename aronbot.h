#ifndef ARONBOT_H
#define ARONBOT_H

#include "bot.h"
#include <vector>

class AronPresident : public PresidentBot {
public:

	virtual string name () {
		return "AronBot";
	}

	virtual void init(int players, int playerIndex, vector<int> cards) {

	}

	virtual vector<int> makeMove( bool newRound ) {
		return vector<int>();
	}

	virtual void moveCallback(int player, vector<int>) {

	}
};

#endif