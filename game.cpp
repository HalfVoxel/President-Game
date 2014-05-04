#include "bot.h"
#include <vector>
#include <map>
#include "bots/humanbot.h"
#include "bots/aronbot.h"
#include <algorithm>
#include <iostream>

using namespace std;

struct Player {
	PresidentBot* bot;
	int rank;
	vector<int> hand;

	Player ( PresidentBot* bot ) : bot(bot), rank(9999) {}
};

bool operator < ( const Player& lhs, const Player& rhs ) {
	return lhs.rank < rhs.rank;
}

bool isWild ( int c ) {
	return c == 2 || c == 3;
}

vector<int> getMove ( const Player& player, bool newRound, int* lastValue, int lastCount ) {
	// Move
	vector<int> move = player.bot->makeMove(newRound);
	
	// check if player has enough cards
	map<int,int> usedCards;
	for ( int i = 0; i < move.size(); i++ ) usedCards[move[i]]++;

	map<int,int> handCards;
	for ( int i = 0; i < player.hand.size(); i++ ) handCards[player.hand[i]]++;

	for ( auto it = usedCards.begin(); it != usedCards.end(); it++ ) {
		if ( handCards[(*it).first] < (*it).second ) {
			cout << "Player " << player.bot->name() << " made an invalid move. Used " << (*it).second << " " << (*it).first << "s but only had " << handCards[(*it).first] << endl;
			return vector<int>();
		}
	}

	if ( move.size () > 0 ) {
		// check that all cards are same value (at least one non-wild)
		int nonWild = -1;
		int totalWild = 0;
		for ( int c : move ) {
			if ( !isWild (c) ) {
				if ( nonWild != -1 && nonWild != c ) {
					cout << "Player " << player.bot->name() << " made an invalid move. Used multiple values of non-wildcards" << endl;
					return vector<int>();
				} else {
					nonWild = c;
				}
			} else {
				totalWild++;
			}
		}

		if ( nonWild == -1 ) {
			cout << "Player " << player.bot->name() << " made an invalid move. Only used wildcards." << endl;
			return vector<int>();
		}
		// check that there are no wild cards if last move
		else if ( player.hand.size() - move.size() == 0 && totalWild > 0 ) {
			cout << "Player " << player.bot->name() << " made an invalid move. Cannot end game with wildcards." << endl;
			return vector<int>();
		}
		// check if move beats previous
		else if ( *lastValue == -1 || (nonWild > *lastValue && move.size() >= lastCount) ) {
			*lastValue = nonWild;
		} else {
			cout << "Player " << player.bot->name() << " made an invalid move. Did not beat last player's cards." << endl;
			return vector<int>();
		}
	}
	return move;
}

void printRanks ( vector<Player> players ) {
	sort( players.begin(), players.end() );

	for (Player player : players ) {
		cout << min((int)players.size(), player.rank) << "........\t" << player.bot->name() << endl;
	}
}

int main () {
	// Init players
	vector<Player> players;
	players.push_back(Player(new HumanPresident()));
	players.push_back(Player(new HumanPresident()));
	players.push_back(Player(new HumanPresident()));
	players.push_back(Player(new HumanPresident()));
	vector<int> cards;
	for(int i = 2; i <= MAX_CARD_VALUE; i++){
		for(int j = 0; j < 4; ++j) cards.push_back(i);
	}
	random_shuffle(cards.begin(), cards.end());
	//vector<vector<int> > hands (players.size());
	//vector<int> rank (players.size());

	int cardsEach = cards.size() / players.size();
	for(int i = 0; i < players.size(); ++i){
		for(int j = 0; j < cardsEach; j++){
			players[i].hand.push_back(cards.back());
			cards.pop_back();
		}
	}

	random_shuffle(players.begin(), players.end());
	for(int i = 0; i < players.size(); ++i){
		players[i].bot->init(players.size(), i, players[i].hand);
	}
	int lastValue = -1, lastCount = -1;
	int lastValidPlayer = -1;
	int cur = 0;
	int numPassed = 0;
	while ( true ) {
		int playersLeft = players.size();
		for(int i = 0; i < players.size(); i++){
			if(players[i].hand.empty()) playersLeft--;
		}
		if(playersLeft == 1) {
			break;
		}

		if(numPassed == players.size()) {
			cout << "No players played cards in one round, assuming they cannot and thus they loose." << endl;
			break;
		}

		int nextCur = (cur + 1) % players.size();
		if(players[cur].hand.empty()) cur = nextCur;
		else {
			bool newRound = false;

			if ( lastValidPlayer == cur || ( lastValidPlayer != -1 && players[lastValidPlayer].hand.empty() ) ) {
				// New round
				lastValue = -1;
				lastCount = -1;
				newRound = true;
				numPassed = 0;
			}

			vector<int> move = getMove ( players[cur], newRound, &lastValue, lastCount );

			if ( move.empty() ) {
				// Pass
				numPassed++;
			} else {
				lastCount = move.size();
				numPassed = 0;
			}

			// Inform players about the move
			for(int i = 0; i < players.size(); i++){
				players[i].bot->moveCallback(cur, move);
			}
			
			// remove cards from array
			for(int i = 0; i < move.size(); i++){
				auto v = find(players[cur].hand.begin(), players[cur].hand.end(), move[i]);
				players[cur].hand.erase(v);
			}
			
			if ( players[cur].hand.empty() ) {
				cout << "Player " << cur << " has finished!" << endl;
				players[cur].rank = players.size() - playersLeft + 1;
			}
			cur = nextCur;
		}
	}

	cout << "The game has ended!" << endl;
	printRanks (players);
}