/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Player {
private:
	//private members
	string _name;
	int _num_of_cards;
	vector<Card> _vec_of_cards; //vector of cards

	Player();
	
public:
	//public members
	Player(string, int);
	Player(const Player& player);
	Player& operator=(const Player& player) { _name = player._name; _vec_of_cards = player._vec_of_cards; return *this; };
	~Player();
	
	bool play(Card&);
	int const get_num_of_cards() const;
	std::string const get_name() const;
	bool draw_card(int current);
	friend std::ostream& operator << (std::ostream &os, const Player &p); //operator << for Player. print name and all cards.
	
};

#endif



