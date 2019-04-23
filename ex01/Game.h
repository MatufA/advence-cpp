/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Card.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Game {
private:
	//private members and functions
	Game(const Game&);
	Game& operator=(const Game&);
	
	Card _current_card;
	vector<Player> _players_vec;
	int _current_player;
	int _direction;
	int _num_of_players;
    int _num_of_cards;
	
	int nextTurn(const Card&);
	bool isGameOver(const Player&) const;
	
	
public:
	//public members and functions
	Game();
	~Game();
	
	void start();
};
#endif

