/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#include "Player.h"


    Player :: Player(string name, int num_of_cards): _name(name), _num_of_cards (num_of_cards){
        // create a vector of cards.
        for (int i = 0; i < _num_of_cards; i++) {
            this->_vec_of_cards.push_back(Card::generate_card());
        }
    }
    
    Player::Player(const Player& player){
        // copy name
        this->_name = player.get_name();
        // copy cards.
        this->_vec_of_cards.assign(player._vec_of_cards.begin(), player._vec_of_cards.end());
    }
    
	Player::~Player(){
	    // delete all cards from vector.
	    _vec_of_cards.clear();
	}
    
    bool Player :: play(Card& current){ // true - if player put a legal card, false - took a card
        int choosen_card;
        // choose a card.
        std::cin >> choosen_card;
        
        //draw a card.
        if(draw_card(choosen_card)) return false;
        
        // otherwise, check if legal
        while (!current.is_legal(_vec_of_cards.at(choosen_card-1))){ 
            std::cout << "You can't put " << _vec_of_cards.at(choosen_card-1);
            std::cout << " on " << current << std::endl;
            // choose a card.
            std::cin >> choosen_card;
            //draw a card.
            if(draw_card(choosen_card)) return false;
        }
        // set choosen as a chosen card.
        current = _vec_of_cards.at(choosen_card-1);
        // remove the choosen one.
        _vec_of_cards.erase(_vec_of_cards.begin() + (choosen_card-1));
        return true;
    }
    
	int const Player::get_num_of_cards() const{ return _vec_of_cards.size(); } //returns player's number of cards
    
    string const Player::get_name() const{ return _name; } //returns player's name
    
    std::ostream& operator << (std::ostream &os, const Player &p){ 
        os << p.get_name() << ", your turn -" << std::endl;
        os << "Your cards:";
       
        for (int i = 0; i < p.get_num_of_cards(); i++) {
            os << " (" << i+1 <<")" << p._vec_of_cards.at(i);
        }
        return os;
    }
    
    bool Player::draw_card(int choosen_card){
        if(choosen_card < 1 || choosen_card > _vec_of_cards.size()){
            _vec_of_cards.push_back(Card::generate_card());
            return true;
        }
        return false;    
    }