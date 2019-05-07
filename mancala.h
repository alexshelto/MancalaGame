/*
Alex Shelton
Mancala Header file:
Project 6C


*/



#ifndef MANCALA_H
#define MANCALA_H

#include "game.h"

namespace main_savitch_14{

class Mancala:public game{
public:
  Mancala();
  who winning()const;
  who next_mover()const;
  game* clone( ) const;
  int evaluate( ) const;
  void stealGems(int index, int position); //used to steal gems if user || computer lands on an empty mancala
  void compute_moves(std::queue<std::string>& moves)const;
  void display_status( )const;
  bool is_game_over( )const;
  bool is_legal(const std::string& move)const;
  void make_move(const std::string& move);
  void restart();
private:
  std::string move;
  int first_move;
  int board[14];//6*2sides + 2 banks = 14
  bool freeMove; //can use for if user gets a free move after(landing in bank)
};



}
#endif
