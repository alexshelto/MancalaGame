/*
Alex Shelton
Mancala Implementation class
Projet 6c

*/

#include "mancala.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "colors.h"
#include <iomanip>

namespace main_savitch_14{

Mancala::Mancala(){
  for(int i = 0; i < 14; i++){
    if(i != 13 && i != 6)
      board[i] = 4;
    else
      board[i] =0;
  }
  freeMove = false;
}

void Mancala::display_status()const{
  std::cout << "---------Game board---------" << std::endl;
  if(game::next_mover() == HUMAN){std::cout<<'|'<<BLUE<<"    Player #1's move:"<<RESET<<"     |" <<"\n|" <<setw(27) <<'|' << std::endl;}
  else{std::cout<<'|' << RED <<"    Player #2's move:"<< RESET<<"     |"<<"\n|"<<setw(27)<<'|'<<std::endl;}
  if(game::next_mover()==COMPUTER){
    std::cout<<'|'<< YELLOW <<  "   12 11 10  9  8  7 "<< RESET << "     |"<<"\n|" <<setw(27) << '|' <<std::endl;
  }
  else{
    std::cout << "|   12 11 10  9  8  7      |\n|"<<setw(27)<<'|'<<std::endl;
  }
  std::cout<<'|'<< RED << "   ["<<board[12]<<"]["<<board[11]<<"]["<<board[10]<<"]["<<board[9]<<"]["<<board[8]<<"]["<<board[7]<<"]"<< RESET<<setw(6)<<'|' <<std::endl;
  std::cout<<'|'<<CYAN << "{"<<board[13]<<"}                  {"<<board[6]<<"}" << RESET<<" |" <<std::endl;
  std::cout<<'|' <<BLUE <<"   ["<<board[0]<<"]["<<board[1]<<"]["<<board[2]<<"]["<<board[3]<<"]["<<board[4]<<"]["<<board[5]<<"]"<<RESET<<setw(6)<<'|' <<std::endl;
  if(game::next_mover()==HUMAN){
    std::cout<<'|'<<setw(27) <<'|'<< YELLOW << "\n|    0  1  2  3  4  5" << RESET << setw(7) << '|' <<std::endl;
  }
  else{
    std::cout<<'|'<<setw(27)<<'|' <<"\n|    0  1  2  3  4  5" <<setw(7) << '|' <<std::endl;
  }
  std::cout << "----------------------------" << std::endl;
}

bool Mancala::is_legal(const std::string& move)const{
// Here the is_legal function needs only to check that the
// player has chosen a bin in the allowable range of numbers.
// In the second phase we can figure out how make the same set of numbers
// or letters work for the two players because we will know whose turn it is.
// The first phase needs to only allow one move to
  int theMove = stoi(move);
  if(game::next_mover() == HUMAN){
    if(theMove < 6 && theMove >= 0 && board[theMove] > 0){//human has slots 1-6 and cant make move on empty slot
      return true;
    }
    else{
      return false;
    }
  }
    else{//computer choose range:
      if(theMove < 13 && theMove >= 7 && board[theMove] > 0)//computer has slots 7-12 and cant make move on empty
      {
        return true;
      }
      else{
        return false;
      }
    }
  }


  void Mancala::make_move(const std::string& move){
    int stealPosition; //used if user can steal gems
    freeMove = false; //assign free move to false at start of ever call:
    int startingP = stoi(move); //starting position = move index:
    int numStones = board[startingP];
    board[startingP] = 0; //simulates picking up all the stones from that index:
    int position; //will be used to calculate freeMove and stealing:

    //moving logic:
    for(int i = startingP+1; i <= numStones+startingP; i++){
      if(i > 13){position = i - 14;}//array has a size of 14:
      else{position = i;}

      //human move:
      if(game::next_mover()==HUMAN){
        if(i != 13){
          board[position]++;
        }
      }//end of human move logic:

      else{//Computer move logic:
        if(i != 6){
          board[position]++;
        }
      }//end of else for computer move:
    }//end of move for loop:

  //calculate ending position to check for steal or move again:
    if(startingP+numStones > 13){
      position = startingP + numStones - 14;
    }
    else{
      position = startingP + numStones;
    }

  //move again/steal:
  if(game::next_mover() == HUMAN){
    if(position == 6){
      //std::cout << YELLOW << "Player 1 sucsessfully landed in mancala\nAwarded another turn!" << RESET << std::endl;
      freeMove = true;
    }
    if(position < 6 && position >= 0 && board[position] == 1){//steal:
      //board[position] = 0; //return it to 0 to add to bank
      //board[6]++;
      stealPosition = (6-position)+6;
      stealGems(stealPosition,position);
    }
  }//end of human again/steal
  else{//computer move:
    if(position == 13){
      //std::cout << YELLOW << "Player 2 sucsessfully landed in mancala\nAwarded another turn!" << RESET << std::endl;
      freeMove = true;
    }
    //steal if statement:
    if(position < 13 && position >= 7 && board[position] == 1){
      //board[position] = 0; //returning the gem to bank
      //board[13]++; //adding the removed to bank
      stealPosition = (13-position)-1;
      stealGems(stealPosition, position);
    }
  }
    if(freeMove != true){
      game::make_move(move);
    }
    std::cout << stoi(move) - 6 << std::endl;
  }//end of make_move function


void Mancala::stealGems(int index, int position){
  int stolen = 0;
  if(index >= 0 && index < 6){//taking humans
    stolen = board[index];
    board[13] += stolen;
    board[index] = 0;
    if(stolen >= 1){
      board[position] = 0;
      board[13]++; //adding the removed to bank
      //std::cout << YELLOW << "Player 2 has stolen your gems!" << RESET << std::endl;
    }
  }
  if(index > 6 && index < 13){//taking computers:
    stolen = board[index];
    board[6] += stolen;
    board[index] = 0;
    if(stolen >= 1){
      board[position] = 0;
      board[6]++;
      //std::cout << YELLOW << "Player 1 has stolen your gems!" << RESET << std::endl;
    }
  }
}


Mancala::who Mancala::winning()const{
  int p1total = 0;
  for(int i = 0; i <= 6; i++){
    p1total += board[i];
  }
  int p2total = 0;
  for(int i = 7; i <= 13; i++){
    p2total += board[i];
  }

  //
  if(p1total > p2total){
    std::cout << "Score: " <<BLUE << p1total<< RESET <<" - " <<RED<<p2total << RESET <<std::endl;
    return HUMAN;
  }
  else if(p2total > p1total){
    std::cout << "Score: " << RED <<p2total << RESET <<" - " << BLUE << p1total <<RESET<<std::endl;
    return COMPUTER;
  }
  else{
    std::cout << "Score: " <<BLUE << p1total<< RESET <<" - " <<RED<< p2total << RESET <<std::endl;
    return NEUTRAL;
  }
}

bool Mancala::is_game_over()const{
  for(int i = 0; i < 14; i++){
    if(board[0] == 0 && board[1] == 0 && board[2] == 0 && board[3] == 0 && board[4] == 0 && board[5] == 0){
      return true;
    }
    if(board[7] == 0 && board[8] == 0 && board[9] == 0 && board[10] == 0 && board[11] == 0 && board[12] == 0)
    {
      return true;
    }
  }
  return false;

}


void Mancala::restart(){
  Mancala();

}

game* Mancala::clone()const{
  return new Mancala(*this);
}

Mancala::who Mancala::next_mover()const{
  if(game::last_mover() == HUMAN){
    return COMPUTER;
  }
  return HUMAN;
}

void Mancala::compute_moves(std::queue<std::string>& moves)const{
  //construct srtring and push through is legal:moves.push to push moves into queue
  //somewhere do a if(islegal(move)) -> moves.push
  string tmp; //used for taking int to string and checking if the move will be legal
  for(int i = 7; i < 13; i++){
    if(board[i] > 0){
      tmp = to_string(i);
      if(is_legal(tmp))
        moves.push(tmp);
    }
  }
}

int Mancala::evaluate()const{
  //counting elements on the board:
  //counting possible computer moves:

  //game* clone = Mancala::clone();

  // int p1 = 0;
  // int p2 = 0;
  // for(int i = 0; i < 13; i++){
  //   if(i < 7){
  //     p1 += i;
  //   }
  //   else
  //     p2 += i;
  // }
  //return(p2-p1);
  return(board[13] - board[6]);
}





}
