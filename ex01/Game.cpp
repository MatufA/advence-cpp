/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#include "Game.h"

Game::Game(): _current_player{0}, _direction(1),
    _num_of_players(0), _num_of_cards(0) {}

Game::~Game(){
    _players_vec.clear();
}

int Game::nextTurn(const Card& card){
    switch(card.get_sign()){
    // player put a plus card.
    case sign::PLUS:
        return 0;
    // player put a stop card.
   case sign::STOP:
        return 2 * Game::_direction;
    // player put a change direction card.
    case sign::CD: 
        Game::_direction *= -1;
    // otherwise.
    default:
        return 1 * Game::_direction;
    }
}

bool Game::isGameOver(const Player& player) const{// checks if players win
    if(player.get_num_of_cards() == 0){
        std::cout << player.get_name() << " wins!" << std::endl;
        return true;
    } 
    return false;
}

void Game::start(){
    // Number of players
    std::cout << "How many players?" << std::endl; 
    std::cin >> Game::_num_of_players;
    if(_num_of_players < 1){
        std::cout << "Number of players is invald - Game Over!" << std::endl;
        return;
    }
    // Number of cards
    std::cout << "How many cards?" << std::endl; 
    std::cin >> Game::_num_of_cards;
    if(_num_of_cards < 1){
        std::cout << "Number of cards is invald - Game Over!" << std::endl;
        return;
    }
    
    // create Players
    for (int i = 0; i < Game::_num_of_players; i++) {
        std::string name;
        std::cout << "player number " << i+1 << " name?" << std::endl;
        std::cin >> name;
        Player p = Player(name, Game::_num_of_cards);
        _players_vec.push_back(p);
    }
    
    _current_card = Card::generate_card();
    
    // show current card
    std::cout << "current: " << Game::_current_card << std::endl;
    // player turn
    std::cout << _players_vec.at(Game::_current_player) << std::endl;
    bool is_draw = _players_vec.at(Game::_current_player).play(Game::_current_card);
    // check if player win.
    Player prev_player = _players_vec.at(Game::_current_player);
    // change to next.
    if(is_draw) Game::_current_player += 1 * nextTurn(Game::_current_card);
    else Game::_current_player += 1 * Game::_direction;
    // escape negatives numbers.
    Game::_current_player = (Game::_current_player + Game::_num_of_players) % Game::_num_of_players;
    
    // run until end of game
    while(!isGameOver(prev_player)){
        // show current card
        std::cout << "current: " << Game::_current_card << std::endl;
        // player turn
        std::cout << _players_vec.at(Game::_current_player) << std::endl;
        // player plays.
        is_draw = _players_vec.at(Game::_current_player).play(_current_card);
        // check if player win.
        prev_player = _players_vec.at(Game::_current_player);
        // next turn
        if(is_draw) Game::_current_player += 1 * nextTurn(Game::_current_card);
        else Game::_current_player += 1 * Game::_direction;
        // escape negatives numbers.
        Game::_current_player = (Game::_current_player + Game::_num_of_players) % Game::_num_of_players;
    }
}
