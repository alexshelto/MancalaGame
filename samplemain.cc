/*****************************************************
Main to run the mancala game

Alexander Shelton
*************************************************************/
#include<iostream>
#include "mancala.h"
using namespace std;
using namespace main_savitch_14;


int main(){
    Mancala stonegame;
	game::who winner;
	winner=stonegame.play();
	if (winner == game::HUMAN)
		std::cout<<"YOU WIN!\n";
	else
		std::cout<<"YOU LOSE!\n";
return 0;
}
